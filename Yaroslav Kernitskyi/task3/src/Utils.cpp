#include "Utils.hpp"

bool is_cpp_extension(std::string_view extension)
{
    return extension == ".h" || extension == ".hpp" || extension == ".c" || extension == ".cpp";
}

bool is_valid_project_path(const fs::path &path)
{
    return fs::exists(path) && fs::is_directory(path);
}