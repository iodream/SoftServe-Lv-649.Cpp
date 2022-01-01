#ifndef PROJECTANALYSIS_HPP
#define PROJECTANALYSIS_HPP

#include "ProjectAnalysisInfo.hpp"
#include "Utils.hpp"

#include <optional>
#include <mutex>
#include <filesystem>
namespace fs = std::filesystem;

std::optional<fs::path> get_path_with_mutex(fs::recursive_directory_iterator &i, std::mutex &mutex);
ProjectAnalysisInfo analyze_project(fs::path root, const std::size_t thread_count);

#endif /* PROJECTANALYSIS_HPP */
