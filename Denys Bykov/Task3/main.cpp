#include "ArgParser.hpp"
#include "Config.hpp"
#include "Analyzer.hpp"

#include <chrono>
#include <sstream>
#include <iomanip>
#include <fstream>

using namespace std;
using namespace chrono;
namespace fs = std::filesystem;

void report_result(
    ostream& os,
    pair<int, BaseAnalyzer::Stat> res,
    milliseconds etime
) {
    int max_res_len{35};
    os << "Statistics for project\n";
    os << std::setw(max_res_len) << std::left;
    os << "Total number of processed files:";
    os << res.first << "\n";
    os << std::setw(max_res_len) << std::left;
    os << "Count of blank lines:";
    os << res.second.comment_lines_num << "\n";
    os << std::setw(max_res_len) << std::left;
    os << "Count of comment lines:";
    os << res.second.blank_lines_num << "\n";
    os << std::setw(max_res_len) << std::left;
    os << "Count of code lines:";
    os << res.second.code_lines_num << "\n";
    os << std::setw(max_res_len) << std::left;
    os << "Time of execution(ms):";
    os << etime.count() << "\n";
}

int validate_args(const ArgParser::Result& args, stringstream& msg) {
    if (!args.source_specified) {
        msg << "Please specify project source dircetory\n";
        return 1;
    }

    if (!fs::exists(fs::path(args.source_d)) ||
        !fs::is_directory(fs::path(args.source_d))) {
        msg << "Unable to find specified source source directory\n";
        return 1;
    }

    if (args.output_to_file) {
        auto out_dir = fs::path(args.output_f).parent_path();
        if (out_dir.string() != string()) {
            if (!fs::exists(out_dir) || !fs::is_directory(out_dir)) {
                msg << "Unable to find directory for output\n";
                return 1;
            }
        }
    }

    if (args.threads_num <= 0) {
        msg << "Incorrect number of threads specified\n";
        return 1;
    }
    return 0;
}

int main(int argc, const char **argv) {
    try {
        auto t1 = high_resolution_clock::now();
        ArgParser arg_parser{argc, argv};
        auto args = arg_parser.Parse();

        if (args.help_requested) {
            arg_parser.PrintHelp();
            return 0;
        }

        stringstream msg;
        auto validation_result = validate_args(args, msg);
        if (validation_result) {
            cout << msg.str();
            return validation_result;
        }

        C_CPPAnalyzer analyzer{Config{args}};
        auto res = analyzer.Analyze();

        auto t2 = high_resolution_clock::now();
        if (args.output_to_file) {
            ofstream file{fs::path{args.output_f}};
            if (!file) {
                cout << "Unable to open/create output file\n";
                cout << "Printing result to standard output\n";
                report_result(cout, res, duration_cast<milliseconds>(t2 - t1));
            }
            report_result(file, res, duration_cast<milliseconds>(t2 - t1));
        }
        else
            report_result(cout, res, duration_cast<milliseconds>(t2 - t1));
    }
    catch (const exception& ex) {
        cout << "Error: " << ex.what() << "\n";
        return 1;
    }
    return 0;
}
