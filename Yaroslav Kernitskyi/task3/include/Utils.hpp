#ifndef UTILS_HPP
#define UTILS_HPP

#include <string_view>
#include <filesystem>
namespace fs = std::filesystem;

bool is_cpp_extension(std::string_view extension);
// Does not work for paths with non ascii characters
bool is_valid_project_path(const fs::path &path);

#endif /* UTILS_HPP */
