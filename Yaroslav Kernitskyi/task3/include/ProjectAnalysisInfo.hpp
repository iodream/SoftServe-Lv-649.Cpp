#ifndef PROJECTANALYSISINFO_HPP
#define PROJECTANALYSISINFO_HPP

#include "FileAnalysis.hpp"

#include <ostream>
#include <filesystem>

namespace fs = std::filesystem;

class ProjectAnalysisInfo
{
public:
    ProjectAnalysisInfo(const fs::path path);
    void add(const FileAnalysisInfo &info);
    friend std::ostream &operator<<(std::ostream &os, const ProjectAnalysisInfo &info);

private:
    fs::path path;
    std::size_t comment_lines_count{0};
    std::size_t code_lines_count{0};
    std::size_t blank_lines_count{0};
    std::size_t files_count{0};
};

#endif /* PROJECTANALYSISINFO_HPP */
