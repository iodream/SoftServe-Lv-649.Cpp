#include "gtest/gtest.h"

#include "ArgParser.hpp"
#include "Config.hpp"
#include "Analyzer.hpp"

using namespace std;
namespace fs = std::filesystem;

class ArgParserTest: public testing::Test {
public:
    vector<string> arg_set_1{};
    vector<string> arg_set_2{};
    vector<string> arg_set_3{};
    vector<string> arg_set_4{};

    ArgParserTest() {}

    void SetUp() {
        arg_set_1 = {"test", "-S", "."};
        arg_set_2 = {"test"};
        arg_set_3 = {"test", "-S", ".", "-O", "./out.txt"};
        arg_set_4 = {"test", "-H"};
    }

    void TearDown() {}
    ~ArgParserTest() {}
};

TEST_F(ArgParserTest, ArgSet1)
{
    int argc = static_cast<int>(arg_set_1.size());
    const char** argv{new const char*[argc]};
    for (int i = 0; i < argc; i++) {
        argv[i] = arg_set_1[i].c_str();
    }

    ArgParser arg_parser{argc, argv};
    auto info = arg_parser.Parse();
    EXPECT_EQ (false, info.help_requested);
    EXPECT_EQ (true, info.source_specified);
    EXPECT_EQ (false, info.output_to_file);
    EXPECT_EQ (string(argv[2]), info.source_d);
    EXPECT_EQ (string(), info.output_f);

    delete[] argv;
}

TEST_F(ArgParserTest, ArgSet2)
{
    int argc = static_cast<int>(arg_set_2.size());
    const char** argv{new const char*[argc]};
    for (int i = 0; i < argc; i++) {
        argv[i] = arg_set_2[i].c_str();
    }

    try {
        ArgParser arg_parser{argc, argv};
        auto info = arg_parser.Parse();
        FAIL() << "Expected ArgParserError";
    }
    catch(const ArgParserError& ex) {
        EXPECT_EQ(ex.what(), string("Not enough arguments"));
    }
    catch(...) {
        FAIL() << "Expected ArgParserError";
    }

    delete[] argv;
}

TEST_F(ArgParserTest, ArgSet3)
{
    int argc = static_cast<int>(arg_set_3.size());
    const char** argv{new const char*[argc]};
    for (int i = 0; i < argc; i++) {
        argv[i] = arg_set_3[i].c_str();
    }

    ArgParser arg_parser{argc, argv};
    auto info = arg_parser.Parse();
    EXPECT_EQ (false, info.help_requested);
    EXPECT_EQ (true, info.source_specified);
    EXPECT_EQ (true, info.output_to_file);
    EXPECT_EQ (string(argv[2]), info.source_d);
    EXPECT_EQ (string(argv[4]), info.output_f);

    delete[] argv;
}

TEST_F(ArgParserTest, ArgSet4)
{
    int argc = static_cast<int>(arg_set_4.size());
    const char** argv{new const char*[argc]};
    for (int i = 0; i < argc; i++) {
        argv[i] = arg_set_4[i].c_str();
    }

    ArgParser arg_parser{argc, argv};
    auto info = arg_parser.Parse();
    EXPECT_EQ (true, info.help_requested);

    delete[] argv;
}

class AnalyzerTest: public testing::Test {
public:
    vector<string> arg_set_1{};
    fs::path test_data_dir{"test_data"};
    fs::path old_path{fs::current_path()};

    AnalyzerTest() {}

    void SetUp() {
        arg_set_1 = {"test", "-S", test_data_dir.string()};
        if (!fs::exists(test_data_dir)) {
            fs::current_path(fs::path{".."});
            if (!fs::exists(test_data_dir)) {
                fs::current_path(fs::path{".."});
                if (!fs::exists(test_data_dir)) {
                    FAIL() << "Failed to locate test_data";
                }
            }
        }
    }

    void TearDown()
    {
        fs::current_path(old_path);
    }
    ~AnalyzerTest() {}
};

TEST_F(AnalyzerTest, FormTasks)
{
    int argc = static_cast<int>(arg_set_1.size());
    const char** argv{new const char*[argc]};
    for (int i = 0; i < argc; i++) {
        argv[i] = arg_set_1[i].c_str();
    }

    ArgParser arg_parser{argc, argv};
    C_CPPAnalyzer analyzer{Config{arg_parser.Parse()}};
    EXPECT_EQ (4, analyzer.FormTasks());

    auto tasks = analyzer.GetTasks();
    vector<string> tasks_vec{};
    while(!tasks.empty()) {
        tasks_vec.push_back(tasks.front().filename().string());
        tasks.pop();
    }

    EXPECT_NE (
        tasks_vec.end(),
        find(tasks_vec.begin(), tasks_vec.end(), "file.c")
    );
    EXPECT_NE (
        tasks_vec.end(),
        find(tasks_vec.begin(), tasks_vec.end(), "file.h")
    );
    EXPECT_NE (
        tasks_vec.end(),
        find(tasks_vec.begin(), tasks_vec.end(), "file.cpp")
    );
    EXPECT_NE (
        tasks_vec.end(),
        find(tasks_vec.begin(), tasks_vec.end(), "file.hpp")
    );

    delete[] argv;
}

TEST_F(AnalyzerTest, FileC)
{
    int argc = static_cast<int>(arg_set_1.size());
    const char** argv{new const char*[argc]};
    for (int i = 0; i < argc; i++) {
        argv[i] = arg_set_1[i].c_str();
    }

    ArgParser arg_parser{argc, argv};
    C_CPPAnalyzer analyzer{Config{arg_parser.Parse()}};
    auto stat = analyzer.AnalyzeFile(test_data_dir / fs::path{"file.c"});

    EXPECT_EQ (0, stat.comment_lines_num);
    EXPECT_EQ (0, stat.code_lines_num);
    EXPECT_EQ (0, stat.blank_lines_num);

    delete[] argv;
}

TEST_F(AnalyzerTest, FileH)
{
    int argc = static_cast<int>(arg_set_1.size());
    const char** argv{new const char*[argc]};
    for (int i = 0; i < argc; i++) {
        argv[i] = arg_set_1[i].c_str();
    }

    ArgParser arg_parser{argc, argv};
    C_CPPAnalyzer analyzer{Config{arg_parser.Parse()}};
    auto stat = analyzer.AnalyzeFile(test_data_dir / fs::path{"file.h"});

    EXPECT_EQ (7, stat.comment_lines_num);
    EXPECT_EQ (11, stat.code_lines_num);
    EXPECT_EQ (3, stat.blank_lines_num);

    delete[] argv;
}

TEST_F(AnalyzerTest, FileCPP)
{
    int argc = static_cast<int>(arg_set_1.size());
    const char** argv{new const char*[argc]};
    for (int i = 0; i < argc; i++) {
        argv[i] = arg_set_1[i].c_str();
    }

    ArgParser arg_parser{argc, argv};
    C_CPPAnalyzer analyzer{Config{arg_parser.Parse()}};
    auto stat = analyzer.AnalyzeFile(test_data_dir / fs::path{"file.cpp"});

    EXPECT_EQ (9, stat.comment_lines_num);
    EXPECT_EQ (113, stat.code_lines_num);
    EXPECT_EQ (17, stat.blank_lines_num);

    delete[] argv;
}

TEST_F(AnalyzerTest, FileHPP)
{
    int argc = static_cast<int>(arg_set_1.size());
    const char** argv{new const char*[argc]};
    for (int i = 0; i < argc; i++) {
        argv[i] = arg_set_1[i].c_str();
    }

    ArgParser arg_parser{argc, argv};
    C_CPPAnalyzer analyzer{Config{arg_parser.Parse()}};
    auto stat = analyzer.AnalyzeFile(test_data_dir / fs::path{"file.hpp"});

    EXPECT_EQ (19, stat.comment_lines_num);
    EXPECT_EQ (0, stat.code_lines_num);
    EXPECT_EQ (1, stat.blank_lines_num);

    delete[] argv;
}

TEST_F(AnalyzerTest, Analyze)
{
    int argc = static_cast<int>(arg_set_1.size());
    const char** argv{new const char*[argc]};
    for (int i = 0; i < argc; i++) {
        argv[i] = arg_set_1[i].c_str();
    }

    ArgParser arg_parser{argc, argv};
    C_CPPAnalyzer analyzer{Config{arg_parser.Parse()}};
    auto res = analyzer.Analyze();

    EXPECT_EQ (4, res.first);
    EXPECT_EQ (35, res.second.comment_lines_num);
    EXPECT_EQ (124, res.second.code_lines_num);
    EXPECT_EQ (21, res.second.blank_lines_num);

    delete[] argv;
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
