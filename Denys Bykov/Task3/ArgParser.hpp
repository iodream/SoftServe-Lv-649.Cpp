#ifndef ARGPARSER_HPP_SENTRY
#define ARGPARSER_HPP_SENTRY

#include <exception>
#include <vector>
#include <string>
#include <iostream>
#include <utility>

#define STD_THREADS_NUM 4

class ArgParserError: public std::exception {
public:
    explicit ArgParserError(const char* message)
        : msg_(message) {}

    explicit ArgParserError(const std::string& message)
        : msg_(message) {}

    virtual ~ArgParserError() noexcept {}
    virtual const char* what() const noexcept {
       return msg_.c_str();
    }

protected:
    std::string msg_;
};

class ArgParser {
    const int argc;
    const char** argv;
public:
    struct Result {
        std::string source_d;
        std::string output_f;
        int threads_num{STD_THREADS_NUM};
        bool source_specified{false};
        bool output_to_file{false};
        bool help_requested{false};
    };
private:
    // remove program name from args and put enquoted args
    // into the single sntrings.
    std::vector<std::string> NormalizeArgs(int argc, const char** argv);
public:
    ArgParser(int argc, const char** argv) : argc{argc}, argv{argv} {}
    Result Parse();
    void PrintHelp();
};

#endif
