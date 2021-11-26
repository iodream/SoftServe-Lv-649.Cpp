#ifndef CONFIG_HPP_SENTRY
#define CONFIG_HPP_SENTRY

#include <vector>
#include <string>
#include <filesystem>

#include "ArgParser.hpp"

class ConfigError: public std::exception {
public:
    explicit ConfigError(const char* message)
        : msg_(message) {}

    explicit ConfigError(const std::string& message)
        : msg_(message) {}

    virtual ~ConfigError() noexcept {}
    virtual const char* what() const noexcept {
       return msg_.c_str();
    }

protected:
    std::string msg_;
};

class Config {
public:
    enum class Lang {
        c_cpp
    };
public:
    std::vector<std::string> extensions;
    Lang lang;
    std::filesystem::path source_d;
    std::filesystem::path output_f;
    int threads_num;
    bool output_to_file;
private:
    void FillExtensions();
public:
    Config(const ArgParser::Result& args, Lang lang=Lang::c_cpp);
};

#endif
