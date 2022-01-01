#include "FileAnalysis.hpp"

#include <catch2/catch_test_macros.hpp>

#include <sstream>
#include <iostream>

// should be done like this?
// or introducing proper mockup?
// or just reading file from directory?

TEST_CASE("Just empty stream")
{
    std::stringstream ss;
    ss << "";

    auto result = analyze(ss);
    REQUIRE(result.comment_lines_count == 0);
    REQUIRE(result.blank_lines_count == 0);
    REQUIRE(result.code_lines_count == 0);
}

TEST_CASE("Only blank lines", "[Blank lines]")
{
    std::stringstream ss;
    ss
        << "\n"        /* empty line */
        << "   \n"     /* line with spaces */
        << "\t\t\t\n"; /* line with tabs */
    auto result = analyze(ss);
    REQUIRE(result.blank_lines_count == 3);
}

TEST_CASE("Code with blank lines", "[Blank lines]")
{
    std::stringstream ss;
    ss << R"(
int main(){

}

)";
    auto result = analyze(ss);
    REQUIRE(result.blank_lines_count == 3);
}

TEST_CASE("Multiline comment with blank lines", "[Blank lines][Comments][Multiline]")
{
    std::stringstream ss;
    ss << R"(
/* multiline comment

with some 

blank lines inside */
)";

    auto result = analyze(ss);
    REQUIRE(result.comment_lines_count == 5);
    REQUIRE(result.blank_lines_count == 3);
}

TEST_CASE("Single line comment", "[Comments][Single line]")
{
    std::stringstream ss;
    ss << R"(
// just comment
)";
    auto result = analyze(ss);
    REQUIRE(result.comment_lines_count == 1);
}

TEST_CASE("Single line comments with blank lines", "[Blank lines][Comments][Single line]")
{
    std::stringstream ss;
    ss << R"(
// just comment

)";
    auto result = analyze(ss);
    REQUIRE(result.comment_lines_count == 1);
    REQUIRE(result.blank_lines_count == 2);
}

TEST_CASE("Single line comment with escaped newline", "[Comments][Single line]")
{
    std::stringstream ss;
    ss << R"(
// comment\
comment continued\
it can go on like this
)";

    auto result = analyze(ss);
    REQUIRE(result.comment_lines_count == 3);
}

TEST_CASE("Single line comment inside string", "[Comments][Single line]")
{
    std::stringstream ss;
    ss << R"(
"string with comment inside // comment inside string"
)";

    auto result = analyze(ss);
    REQUIRE(result.comment_lines_count == 0);
}

TEST_CASE("String inside single line comment", "[Comments][Single line]")
{
    std::stringstream ss;
    ss << R"(
// "string inside comment"
)";

    auto result = analyze(ss);
    REQUIRE(result.comment_lines_count == 1);
}

TEST_CASE("Multiline comment inside single line comment", "[Comments][Single line][Multiline]")
{
    std::stringstream ss;
    ss << R"(
// /* multiline comment */
)";

    auto result = analyze(ss);
    REQUIRE(result.comment_lines_count == 1);
}

TEST_CASE("Just multiline comment", "[Comments][Multiline]")
{
    std::stringstream ss;
    ss << "/* multiline comment */\n";

    auto result = analyze(ss);
    REQUIRE(result.comment_lines_count == 1);
    REQUIRE(result.code_lines_count == 0);
    REQUIRE(result.blank_lines_count == 0);
}

TEST_CASE("Multiline comment spanning multiple lines", "[Comments][Multiline]")
{
    std::stringstream ss;
    ss << R"(
/* multiline comment
second line
third line
and so on */
)";

    auto result = analyze(ss);
    REQUIRE(result.comment_lines_count == 4);
}

TEST_CASE("String inside multiline comment", "[Comments][Multiline]")
{
    std::stringstream ss;
    ss << R"(
/* multiline comment
"some string"
and so on */
)";

    auto result = analyze(ss);
    REQUIRE(result.comment_lines_count == 3);
}

TEST_CASE("Multiline comment closing delimiter inside string", "[Comments][Multiline]")
{
    std::stringstream ss;
    ss << R"(
/* multiline comment
"some pretty */ long string"
)";

    auto result = analyze(ss);
    REQUIRE(result.comment_lines_count == 2);
}

TEST_CASE("Simple code lines", "[Code]")
{
    std::stringstream ss;
    ss << R"(
Every line that is not a comment and not blank counts as code.
Validation of c++ code is way out of scope of this task.
)";

    auto result = analyze(ss);
    REQUIRE(result.code_lines_count == 2);
}

TEST_CASE("Code and single line comment", "[Code][Comments][Single line]")
{
    // If we transition from code to comment we must increment code lines even before \n reached
    std::stringstream ss;
    ss << R"(
float pi = 3.14159; // pi constant
// one more comment
)";

    auto result = analyze(ss);
    INFO("Code lines " << result.code_lines_count);
    INFO("comment lines " << result.comment_lines_count);
    REQUIRE(result.code_lines_count == 1);
    REQUIRE(result.comment_lines_count == 2);
}

TEST_CASE("Code and multiline comment", "[Code][Comments][Multiline]")
{
    std::stringstream ss;
    ss << R"(
float pi = 3.14159; /* this line counts as both code and comment line
another constant - e */ float e = 2.71828;
/* comment to test blank line with comment */
)";

    auto result = analyze(ss);
    REQUIRE(result.code_lines_count == 2);
    REQUIRE(result.comment_lines_count == 3);
}

TEST_CASE("Some real world code", "[Code][Comments][Multiline][Single line]")
{
    std::cout << "Test\n";
    std::stringstream ss;
    ss << R"(#ifndef FILEANALYSIS_HPP
#define FILEANALYSIS_HPP

#include <cstddef>
#include <istream>

/* Test */
struct FileAnalysisInfo
{
    std::size_t comment_lines_count = 0;
    std::size_t code_lines_count = 0;
    std::size_t blank_lines_count = 0;
};

// We assume that 'file' is valid cpp source file
// So no unmatched ", /* or */
// Cannot handle raw string literals
FileAnalysisInfo analyze(std::istream &file);

#endif /* FILEANALYSIS_HPP */
)";

    auto result = analyze(ss);
    REQUIRE(result.blank_lines_count == 4);
    REQUIRE(result.comment_lines_count == 5);
    REQUIRE(result.code_lines_count == 12);
}

TEST_CASE("String with escape characters", "[Code]")
{
    std::stringstream ss;
    ss << R"(
auto test = "string\
spanning\
multiple\
lines";
)";

    auto result = analyze(ss);
    REQUIRE(result.code_lines_count == 4);
}

TEST_CASE("Raw string literal", "[Code]")
{
    std::stringstream ss;
    ss << R"escape(
auto test = R"(string
spanning
multiple
lines)";
)escape";

    auto result = analyze(ss);
    REQUIRE(result.code_lines_count == 4);
}