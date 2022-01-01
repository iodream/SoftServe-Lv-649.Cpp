#ifndef FILEANALYSIS_HPP
#define FILEANALYSIS_HPP

#include <cstddef>
#include <istream>

struct FileAnalysisInfo
{
    std::size_t comment_lines_count = 0;
    std::size_t code_lines_count = 0;
    std::size_t blank_lines_count = 0;
};

// We assume that 'file' is valid cpp source file
// So no unmatched ", /* or */
// Cannot handle raw string literals
// Should i handle case of last line not ending with \n?
FileAnalysisInfo analyze(std::istream &file);

#endif /* FILEANALYSIS_HPP */
