#include "FileAnalysis.hpp"

#include <cctype>
#include <iostream>

/*
At the moment lines are classified according to following rules:
1. only spaces, tabs or newline character -> blank_lines++
2. contains code -> code_lines++
3. contains comment -> comment_lines++
4. same as 1 but inside comment -> blank_lines++, comment_lines++;

code_lines + blank_lines + comment_lines != total_lines
*/

FileAnalysisInfo analyze(std::istream &file)
{
    enum class State
    {
        Code,
        String,
        SingleLineComment,
        MultiLineComment
    };
    State state = State::Code;

    FileAnalysisInfo info;

    bool is_current_line_blank = true;
    bool line_has_code = false;

    char previous;
    if (file.get(previous))
    {
        if (previous == '\n')
        {
            info.blank_lines_count++;
        }
        if (!std::isspace(previous))
        {
            is_current_line_blank = false;
            if (previous != '/')
            {
                line_has_code = true;
            }
        }
        if (previous == '"')
        {
            state = State::String;
            line_has_code = true;
        }
    }

    char current;
    while (file.get(current))
    {
        if (!std::isspace(current))
        {
            is_current_line_blank = false;
        }

        switch (state)
        {
        case State::Code:
            // if character cannot be part of comment then this line definitely contains code
            if (previous == '\n' && !std::isspace(current) && current != '/')
            {
                line_has_code = true;
            }

            if (!std::isspace(current) &&
                !(previous == '/' && current == '/') &&
                !(previous == '/' && current == '*') &&
                previous != '\n')
            {
                line_has_code = true;
            }

            // if (previous != '\\' && current == '\n')
            if (current == '\n')
            {
                if (is_current_line_blank)
                {
                    info.blank_lines_count++;
                }
                if (line_has_code)
                {
                    info.code_lines_count++;
                }
                is_current_line_blank = true;
                line_has_code = false;
            }

            if (previous == '/' && current == '/')
            {
                state = State::SingleLineComment;
            }

            if (previous == '/' && current == '*')
            {
                state = State::MultiLineComment;
            }

            if (current == '"')
            {
                state = State::String;
                line_has_code = true;
            }
            break;

        case State::String:
            if (previous != '\\' && current == '"')
            {
                state = State::Code;
            }

            if (current == '\n')
            {
                info.code_lines_count++;
                line_has_code = false;
                is_current_line_blank = true;
            }

            break;

        case State::SingleLineComment:
            // if (previous != '\\' && current == '\n')
            if (current == '\n')
            {
                info.comment_lines_count++;
                if (previous != '\\')
                {
                    state = State::Code;
                }

                if (line_has_code)
                {
                    info.code_lines_count++;
                }

                line_has_code = false;
                is_current_line_blank = true;
            }
            break;

        case State::MultiLineComment:
            if (previous == '*' && current == '/')
            {
                state = State::Code;
                info.comment_lines_count++;
            }
            if (previous != '\\' && current == '\n')
            {
                if (is_current_line_blank)
                {
                    info.blank_lines_count++;
                }
                if (line_has_code)
                {
                    info.code_lines_count++;
                }
                info.comment_lines_count++;
                is_current_line_blank = true;
                line_has_code = false;
            }
            break;

        default:
            // unreachable
            break;
        }

        previous = current;
    }

    return info;
}