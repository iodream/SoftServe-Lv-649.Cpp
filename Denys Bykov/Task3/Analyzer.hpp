#ifndef ANALYZER_HPP_SENTRY
#define ANALYZER_HPP_SENTRY

#include <queue>
#include <utility>
#include <thread>
#include <mutex>
#include <map>

#include "Config.hpp"

class BaseAnalyzer {
public:
    using size_t = int;
    struct Stat {
        size_t blank_lines_num{0};
        size_t comment_lines_num{0};
        size_t code_lines_num{0};
        bool failed{false};
    };
private:
    Config conf;
    std::mutex tasks_mutex{};
    std::queue<std::filesystem::path> tasks{};
private:
    size_t FindTasks(std::filesystem::path path);
    void MergeStat(Stat& stat, const Stat& update) const;
    static void WorkerRoutine(BaseAnalyzer* master, Stat& res);
public:
    BaseAnalyzer(const Config& conf): conf{conf} {}

    // Fills tasks queue and returns it's size
    size_t FormTasks();

    virtual Stat AnalyzeFile(std::filesystem::path path) = 0;

    // Performs multithreaded analisys of tasks
    // returns std::pair which consists of
    //   number of processed files
    //   Stat object
    std::pair<size_t, Stat> Analyze();

    std::queue<std::filesystem::path> GetTasks() const;
};

class C_CPPAnalyzer: public BaseAnalyzer {
    enum class Token {
        token_part,
        cpp_style_comment,
        c_style_comment_begin,
        c_style_comment_end,
    };
    struct ParsingState {
        bool in_c_style_comment{false};
        bool in_cpp_style_comment{false};
        bool curr_line_is_comment{false};
        bool curr_line_is_code{false};
    };
private:
    // Key is a syntax unit and value is a token type
    using parse_map_t = std::map<std::string, Token>;
    parse_map_t parse_map;
private:
    void HandleLine(Stat& stat, const std::string& line, ParsingState& state);
    using iterator_t = std::string::const_iterator;
    void HandleToken(
        Token token_type,
        iterator_t& it,
        iterator_t end,
        ParsingState& state);
    void HandleCPPComment
        (iterator_t& it, iterator_t end, ParsingState& state);
    void HandleCComment
        (iterator_t& it, iterator_t end, ParsingState& state);
    void HandleNonSpaceChar
        (iterator_t& it, iterator_t end, ParsingState& state);
    void SkipStringLiteral
        (iterator_t& it, iterator_t end);
    void UpdateStat(Stat& stat, ParsingState& state);
public:
    C_CPPAnalyzer(const Config& conf);
    Stat AnalyzeFile(std::filesystem::path path);
};

#endif
