#include "Utils.hpp"
#include "ProjectAnalysis.hpp"

#include <string>
#include <iostream>
#include <chrono>
#include <fstream>

fs::path read_valid_project_path()
{
    std::string path_string;
    fs::path path;

    do
    {
        std::cout << "Enter project path: ";
        std::getline(std::cin, path_string);
        path = fs::path(path_string);
    } while (!is_valid_project_path(path));

    return path;
}

std::size_t read_threads_count()
{
    int input;
    do
    {
        std::cout << "Enter threads count: ";
        std::cin >> input;
    } while (std::cin.fail());
    return input;
}

fs::path read_report_file_path()
{
    std::string path;
    std::cout << "Enter report file name: ";
    std::cin.ignore();
    std::getline(std::cin, path);
    return fs::path(path);
}

void print_report(std::ostream &os, const ProjectAnalysisInfo &info, std::chrono::milliseconds execution_time)
{
    std::cout << info << "\n";
    std::cout << "Execution time: " << execution_time.count() << " ms\n";
}

int main()
{
    auto project_path = read_valid_project_path();
    auto threads_count = read_threads_count();
    auto report_path = read_report_file_path();

    auto start_time = std::chrono::high_resolution_clock::now();
    auto analysis_result = analyze_project(project_path, threads_count);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto execution_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    print_report(std::cout, analysis_result, execution_time);

    auto report_file = std::ofstream(report_path);
    if (report_file)
    {
        print_report(report_file, analysis_result, execution_time);
        std::cout << "Results printed to file " << report_path << "\n";
    }
    else
    {
        std::cout << "Failed to open file " << report_path << "\n";
    }
}
