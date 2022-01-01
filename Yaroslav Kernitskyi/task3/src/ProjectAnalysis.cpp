#include "ProjectAnalysis.hpp"

#include <fstream>

std::optional<fs::path> get_path_with_mutex(fs::recursive_directory_iterator &i, std::mutex &mutex)
{
    std::lock_guard<std::mutex> lock(mutex);
    if (i == fs::recursive_directory_iterator{})
    {
        return std::nullopt;
    }
    auto file_path = i->path();
    ++i;

    return file_path;
}

ProjectAnalysisInfo analyze_project(fs::path root, const std::size_t thread_count)
{
    ProjectAnalysisInfo result(root);

    std::vector<std::thread> thread_pool;
    auto directory_iterator = fs::recursive_directory_iterator(root);
    std::mutex mutex;

    for (std::size_t i = 0; i < thread_count; i++)
    {
        thread_pool.push_back(std::thread([&]()
                                          {
                                              std::optional<fs::path> file_path;
                                              while (file_path = get_path_with_mutex(directory_iterator, mutex))
                                              {
                                                  if (is_cpp_extension(file_path->extension().string()))
                                                  {
                                                      auto file = std::ifstream(file_path.value());
                                                      if (file)
                                                      {
                                                          auto file_info = analyze(file);

                                                          mutex.lock();
                                                          result.add(file_info);
                                                          mutex.unlock();
                                                      }
                                                  }
                                              }
                                          }));
    }

    for (auto &t : thread_pool)
    {
        t.join();
    }

    return result;
}