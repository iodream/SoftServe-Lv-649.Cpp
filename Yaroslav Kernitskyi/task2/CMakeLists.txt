cmake_minimum_required(VERSION 3.15.0)
project(AnyType VERSION 0.1.0)

add_library(AnyType INTERFACE)
target_compile_features(AnyType INTERFACE cxx_std_17)

target_include_directories(AnyType INTERFACE
    ${CMAKE_SOURCE_DIR}/include
)

# Get Catch lib
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.0-preview3
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests test.cpp)
target_compile_features(tests PRIVATE cxx_std_17)
target_include_directories(tests PRIVATE
  ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(tests)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
