#include "Analyzer.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <functional>

using namespace std;
using namespace std::filesystem;

// BaseAnalyzer

BaseAnalyzer::size_t BaseAnalyzer::FindTasks(std::filesystem::path path)
{
    size_t count{0};
    for (const auto& p: recursive_directory_iterator(path)) {
        if (is_regular_file(p.status())) {
            auto ext_pos{
                find(
                    conf.extensions.begin(),
                    conf.extensions.end(),
                    p.path().extension().string()
                )
            };

            if (ext_pos != conf.extensions.end())
            {
                count++;
                tasks.push(p.path());
            }
        }
    }
    return count;
}

BaseAnalyzer::size_t BaseAnalyzer::FormTasks()
{
    return FindTasks(conf.source_d);
}

std::queue<std::filesystem::path> BaseAnalyzer::GetTasks() const
{
    return tasks;
}

void BaseAnalyzer::MergeStat(Stat& stat, const Stat& update) const
{
    stat.blank_lines_num += update.blank_lines_num;
    stat.comment_lines_num += update.comment_lines_num;
    stat.code_lines_num += update.code_lines_num;
}

pair<BaseAnalyzer::size_t, BaseAnalyzer::Stat> BaseAnalyzer::Analyze()
{
    pair<size_t, Stat> res;

    auto tasks_num = FormTasks();
    res.first = tasks_num;

    vector<thread> workers;
    vector<Stat> results(conf.threads_num);
    for (int i = 0; i < conf.threads_num; i++) {
        workers.push_back(thread{WorkerRoutine, this, ref(results[i])});
    }

    for (int i = 0; i < conf.threads_num; i++) {
        workers[i].join();
        MergeStat(res.second, results[i]);
    }

    return res;
}

void BaseAnalyzer::WorkerRoutine(BaseAnalyzer* master, Stat& res)
{
    while (true) {
        path task;
        {
            lock_guard<mutex> lock(master->tasks_mutex);
            if (master->tasks.empty())
                break;
            task = master->tasks.front();
            master->tasks.pop();
        }
        auto stat = master->AnalyzeFile(task);
        master->MergeStat(res, stat);
    }
}

// C_CPPAnalyzer

C_CPPAnalyzer::C_CPPAnalyzer(const Config& conf) :
    BaseAnalyzer{conf},
    parse_map{}
{
    parse_map.insert({string{"/"},  Token::token_part});
    parse_map.insert({string{"//"}, Token::cpp_style_comment});
    parse_map.insert({string{"/*"}, Token::c_style_comment_begin});
    parse_map.insert({string{"*"},  Token::token_part});
    parse_map.insert({string{"*/"}, Token::c_style_comment_end});
}

C_CPPAnalyzer::Stat C_CPPAnalyzer::AnalyzeFile(std::filesystem::path path)
{
    Stat res{};
    ifstream file{path};
    if (!file) {
        res.failed = true;
        return res;
    }
    ParsingState state{};
    for (string line; getline(file, line); ) {
        HandleLine(res, line, state);
    }
    return res;
}

void C_CPPAnalyzer::HandleLine
    (Stat& stat, const std::string& line, ParsingState& state)
{
    state.curr_line_is_comment = false;
    state.curr_line_is_code = false;
    // Multiline comment case
    if (state.in_cpp_style_comment) {
        auto it = line.cbegin();
        HandleCPPComment(it, line.cend(), state);
    }
    else {
        if (state.in_c_style_comment)
            state.curr_line_is_comment = true;
        string curr_token{};

        for (auto it = line.cbegin(); it != line.cend(); it++) {
            if (isspace(*it))
                continue;

            curr_token += *it;
            auto parse_result = parse_map.find(curr_token);
            if (parse_result != parse_map.end()) {
                if (parse_result->second != Token::token_part) {
                    it++;
                    HandleToken(parse_result->second, it, line.cend(), state);
                }
                continue;
            }

            HandleNonSpaceChar(it, line.cend(), state);
            curr_token.erase();
        }
    }
    UpdateStat(stat, state);
}

void C_CPPAnalyzer::SkipStringLiteral
    (iterator_t& it, iterator_t end)
{
    string tmp{};
    for (; it != end; it++) {
        if (tmp.size())
            tmp.erase();
        else {
            if (*it == '\\')
                tmp += *it;
            else if (*it == '\"')
                return;
        }
    }
    if (it == end)
        it--;
}

void C_CPPAnalyzer::HandleToken(
    Token token_type,
    iterator_t& it,
    iterator_t end,
    ParsingState& state)
{
    if (!state.in_c_style_comment) {
        if (token_type == Token::cpp_style_comment) {
            HandleCPPComment(it, end, state);
        }
        else if (token_type == Token::c_style_comment_begin) {
            HandleCComment(it, end, state);
        }
    }
    else {
        if (token_type == Token::c_style_comment_end)
            state.in_c_style_comment = false;
    }
    if (it == end)
        it--;
}

void C_CPPAnalyzer::HandleCPPComment
    (iterator_t& it, iterator_t end, ParsingState& state)
{
    state.curr_line_is_comment = true;
    state.in_cpp_style_comment = true;

    bool is_multiline{false};
    for (; it != end; it++) {
        if (isspace(*it))
            continue;
        if (*it == '\\')
            is_multiline = true;
        else
            is_multiline = false;
    }

    state.in_cpp_style_comment = is_multiline;
}

void C_CPPAnalyzer::HandleCComment
    (iterator_t& it, iterator_t end, ParsingState& state)
{
    state.curr_line_is_comment = true;
    state.in_c_style_comment = true;

    string tmp{};
    for (; it != end; it++) {
        if (tmp.size()) {
            if (*it == '/') {
                state.in_c_style_comment = false;
                return;
            }
            tmp.erase();
        }
        else {
            if (*it == '*')
                tmp += *it;
        }
    }
}

void C_CPPAnalyzer::HandleNonSpaceChar
    (iterator_t& it, iterator_t end, ParsingState& state)
{
    if (!state.in_c_style_comment) {
        state.curr_line_is_code = true;
        if (*it == '\"') {
            it++;
            SkipStringLiteral(it, end);
        }
    }
}

void C_CPPAnalyzer::UpdateStat(Stat& stat, ParsingState& state)
{
    bool curr_line_is_blank{true};
    if (state.curr_line_is_comment) {
        curr_line_is_blank = false;
        stat.comment_lines_num++;
    }
    if (state.curr_line_is_code) {
        curr_line_is_blank = false;
        stat.code_lines_num++;
    }
    if (curr_line_is_blank) {
        stat.blank_lines_num++;
    }
}
