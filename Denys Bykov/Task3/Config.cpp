#include "Config.hpp"
#include <fstream>

using namespace std;
using namespace std::filesystem;

void Config::FillExtensions()
{
    switch (lang) {
        case Lang::c_cpp:
            extensions.push_back(".h");
            extensions.push_back(".hpp");
            extensions.push_back(".c");
            extensions.push_back(".cpp");
            break;
        default:
            throw ConfigError("Sepcified language is not supported");
    }
}

Config::Config(const ArgParser::Result& args, Lang lang):
    extensions{},
    lang{lang},
    source_d{args.source_d},
    output_f{args.output_f},
    threads_num{args.threads_num},
    output_to_file{args.output_to_file}
{
    FillExtensions();
    if (!exists(source_d) || !is_directory(source_d))
        throw ConfigError("Unable to find specified source directory");
    if (output_to_file) {
        if (!exists(output_f)) {
            if (!ofstream{output_f})
                throw ConfigError("Unable to create report file");
        }
    }
    if (threads_num <= 0)
        throw ConfigError("Bad number of threads");
}
