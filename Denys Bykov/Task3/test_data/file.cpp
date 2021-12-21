#include "Analyzer.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>

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
                tasks.push(p);
            }
        }
    }
    return count;
} // 27 code lines; 2 comments; 5 blank lines;

BaseAnalyzer::size_t BaseAnalyzer::FormTasks()
{
    return FindTasks(conf.source_d);
}

std::queue<std::filesystem::directory_entry> BaseAnalyzer::GetTasks() const
{
    return tasks;
}

void BaseAnalyzer::MergeStat(Stat& stat, const Stat& update)
{
    stat.blank_lines_num += update.blank_lines_num;
    stat.comment_lines_num += update.comment_lines_num;
    stat.code_lines_num += update.code_lines_num;
}

// C_CPPAnalyzer

C_CPPAnalyzer::C_CPPAnalyzer(const Config& conf) :
    BaseAnalyzer{conf},
    parse_map{}
{
    parse_map.insert({string{"/"},  Token::token_part});
    parse_map.insert({string{"//"}, Token::cpp_style_comment});
    parse_map.insert({string{"/*"}, Token::c_style_comment_begin});
    parse_map.insert({string{"*\""},  Token::token_part});
    /* '\"'? Where did you come from? */
    parse_map.insert({string{"*/"}, Token::c_style_comment_end});
} // 24 + 27 = 51 code lines; 3 + 2 = 5 comments; 5 + 5 = 10 blank lines;

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
} // 14 + 51 = 65 code lines; 1 + 5 = 6 comments; 1 + 10 = 11 blank lines;

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
} // 32 + 65 = 97 code lines; 2 + 6 = 8 comments; 5 + 11 = 16 blank lines;

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
} // 16 + 97 = 113 code lines; 1 + 8 = 9 comments; 1 + 16 = 17 blank lines;
