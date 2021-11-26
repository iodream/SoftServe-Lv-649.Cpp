cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(PrStat VERSION 1.0)
project(Test)

add_executable(PrStat
    main.cpp
    ArgParser.cpp
    Config.cpp
    Analyzer.cpp
)

add_executable(Test
    test.cpp
    ArgParser.cpp
    Config.cpp
    Analyzer.cpp
)

find_package(GTest REQUIRED)

if(MSVC)
  target_compile_options(PrStat PRIVATE /W4 /WX)
endif()
if(CMAKE_COMPILER_IS_GNUCC)
  target_compile_options(PrStat PRIVATE -Wall -Wextra -pedantic -Werror -ggdb)
endif()

target_include_directories(PrStat PUBLIC
    "${PROJECT_BINARY_DIR}"
)

target_link_libraries(PrStat PUBLIC
    pthread
)

target_link_libraries(Test PUBLIC
  gmock
  gtest
  pthread
)
