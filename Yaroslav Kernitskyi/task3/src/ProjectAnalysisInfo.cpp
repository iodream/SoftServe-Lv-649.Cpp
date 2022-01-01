#include "ProjectAnalysisInfo.hpp"

ProjectAnalysisInfo::ProjectAnalysisInfo(const fs::path path) : path(path) {}

void ProjectAnalysisInfo::add(const FileAnalysisInfo &info)
{
    comment_lines_count += info.comment_lines_count;
    code_lines_count += info.code_lines_count;
    blank_lines_count += info.blank_lines_count;
    files_count++;
}

std::ostream &operator<<(std::ostream &os, const ProjectAnalysisInfo &info)
{
    os
        << "Project " << info.path << " with " << info.files_count << " files was analyzed.\n"
        << "Blank lines: " << info.blank_lines_count << "\n"
        << "Code lines: " << info.code_lines_count << "\n"
        << "Comment lines: " << info.comment_lines_count;

    return os;
}