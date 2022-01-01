cmake_minimum_required(VERSION 3.0.0)
project(ProjectAnalyzer LANGUAGES CXX VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(ProjectAnalyzer
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/Utils.cpp
	${CMAKE_SOURCE_DIR}/src/FileAnalysis.cpp
    ${CMAKE_SOURCE_DIR}/src/ProjectAnalysisInfo.cpp
    ${CMAKE_SOURCE_DIR}/src/ProjectAnalysis.cpp
)

target_include_directories(ProjectAnalyzer PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
)

# all my attempts to enable filesystem
#target_compile_features(ProjectAnalyzer PRIVATE cxx_std_17)
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property (TARGET ProjectAnalyzer PROPERTY
    # Enable C++17 standard compliance
    CXX_STANDARD 17
)

# Tests
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.0-preview3
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests
    ${CMAKE_SOURCE_DIR}/test/Test.cpp
    ${CMAKE_SOURCE_DIR}/src/Utils.cpp
	${CMAKE_SOURCE_DIR}/src/FileAnalysis.cpp
    ${CMAKE_SOURCE_DIR}/src/ProjectAnalysisInfo.cpp
    ${CMAKE_SOURCE_DIR}/src/ProjectAnalysis.cpp
)
target_compile_features(tests PRIVATE cxx_std_17)
target_include_directories(tests PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(tests)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
