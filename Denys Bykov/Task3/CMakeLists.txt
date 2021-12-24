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

if(MSVC)
    target_compile_options(PrStat PRIVATE /W4 /WX)
    target_compile_options(Test PRIVATE /W4 /WX /MT)

    find_path(
        GTEST_INCLUDE NAMES
        "gmock/gmock.h" "gtest/gtest.h"
        HINTS ENV Path
        NO_CACHE
        REQUIRED
    )

    find_library(
        GTEST_LIB NAMES
        "gtest.lib"
        HINTS ENV Path
        NO_CACHE
        REQUIRED
    )
    find_library(
        GMOCK_LIB NAMES
        "gmock.lib"
        HINTS ENV Path
        NO_CACHE
        REQUIRED
    )

  list(APPEND INCLUDE_DIRS
      ${GTEST_INCLUDE}
  )
  list(APPEND TEST_LIBS ${GTEST_LIB} ${GMOCK_LIB})

endif()
if(CMAKE_COMPILER_IS_GNUCC)
    target_compile_options(PrStat PRIVATE -Wall -Wextra -pedantic -Werror -ggdb)
    target_compile_options(Test PRIVATE -Wall -Wextra -pedantic -Werror -ggdb)

    list(APPEND EXTRA_LIBS pthread)
    list(APPEND TEST_LIBS gmock gtest)
    find_package(GTest REQUIRED)
endif()

target_include_directories(PrStat PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${INCLUDE_DIRS}"
)

target_include_directories(Test PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${INCLUDE_DIRS}"
)

target_link_libraries(PrStat PUBLIC
    ${LIBS}
    ${EXTRA_LIBS}
)

target_link_libraries(Test PUBLIC
    ${TEST_LIBS}
    ${EXTRA_LIBS}
)
