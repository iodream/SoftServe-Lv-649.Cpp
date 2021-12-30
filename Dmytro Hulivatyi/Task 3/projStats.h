#ifndef PROJSTATS_H
#define PROJSTATS_H

#include <vector>
#include <string>

//counts lines which are commented out as single line comments at the start of the string
void CountSingleCommentLines(const std::vector<std::string> &lines, int& nRes);

//find multiline comments and count the lines
void CountMultiLineCommentLines(const std::vector<std::string> &lines, int& nRes);

//count blank lines or lines with whitespace-only
void CountBlankLines(const std::vector<std::string> &lines, int& nRes);

#endif // PROJSTATS_H
