cmake_minimum_required(VERSION 3.15)

project(StringList LANGUAGES CXX)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.0-preview3
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests
	Test.cpp
	${CMAKE_SOURCE_DIR}/src/String.cpp
	${CMAKE_SOURCE_DIR}/src/Node.cpp
	${CMAKE_SOURCE_DIR}/src/StringList.cpp)
	
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

target_include_directories(tests PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/include
)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(tests)