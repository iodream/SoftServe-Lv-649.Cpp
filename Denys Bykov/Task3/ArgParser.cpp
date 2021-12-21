#include "ArgParser.hpp"

#include <iomanip>

using namespace std;

vector<string> ArgParser::GetNormalizedArgs()
{
    vector<string> res{};
    bool is_enquoted = false;
    const string quote_s{"\""};
    string enq_arg{};
    for (int i = 1; i < argc; i++) {
        string tmp{argv[i]};

        if (tmp.find(quote_s) != string::npos) {
            if (!is_enquoted) {
                is_enquoted = true;
                enq_arg = string{tmp.begin() + 1, tmp.end()};
                continue;
            }
            else {
                is_enquoted = false;
                enq_arg += string{tmp.begin(), tmp.end() - 1};
                swap(enq_arg, tmp);
            }
        }

        if (is_enquoted) {
            enq_arg += tmp;
        }
        else {
            res.push_back(tmp);
        }
    }
    return res;
}

ArgParser::Result ArgParser::Parse()
{
    auto args = GetNormalizedArgs();
    if (args.size() < 1)
        throw ArgParserError("Not enough arguments");

    auto move_it = [&args](vector<string>::iterator& it, const string& opt) {
        if ((++it) == args.end())
            throw ArgParserError(string{"Missed value for option "}.append(opt));
    };

    Result res;
    for (auto it = args.begin(); it != args.end(); it++) {
        if ((*it) == string("--help") || (*it) == string("-H"))
            res.help_requested = true;
        else if ((*it) == string("--source") || (*it) == string("-S")) {
            move_it(it, *it);
            res.source_specified = true;
            res.source_d = *it;
        }
        else if ((*it) == string("--out") || (*it) == string("-O")) {
            move_it(it, *it);
            res.output_to_file = true;
            res.output_f = *it;
        }
        else if ((*it) == string("--tnum") || (*it) == string("-T")) {
            move_it(it, *it);
            try {
                res.threads_num = stoi(*it);
            }
            catch (const exception&) {
                res.threads_num = -1;
            }
        }
        else if ((*it) != string{})
            throw ArgParserError(string{"Unknown option: "}.append(*it));
    }
    return res;
}

void ArgParser::PrintHelp()
{
    const int max_opt_len{35};
    cout << "Usage:\n\n";
    cout << "[options] -S <path-to-source>\n\n";
    cout << "Specify a source directory of the project you need statistic for.\n\n";
    cout << "Options:\n";
    cout << std::setw(max_opt_len) << std::left;
    cout << "  -S, --source <path-to-source>";
    cout << "Specify source directory.\n";
    cout << std::setw(max_opt_len) << std::left;
    cout << "  -O, --out <path-to-output>";
    cout << "Enable report to file and specify\n";
    cout << "" << std::setw(max_opt_len) << std::right << "";
    cout << "report file name.\n";
    cout << std::setw(max_opt_len) << std::left;
    cout << "  -T, --thum <threads-to-use>";
    cout << "Specify number of threads to be used.\n";
}
