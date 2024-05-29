cmake_minimum_required(VERSION 3.29.3)
project(cpp_examples)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

enable_testing()
target_precompile_headers(cpp_examples, PUBLIC pch.h)
add_executable(cpp_examples tasks/binarygap.cpp)

include(GoogleTest)
gtest_discover_tests(cpp_examples)
