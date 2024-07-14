cmake_minimum_required(VERSION 3.16.3)
project(cpp_examples)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

#define executable target
file(GLOB TASK_SOURCES "tasks/*.cpp")
file(GLOB GMOCK_SOURCES "gmock/*.h" "gmock/*.cpp")
add_executable(cpp_examples ${TASK_SOURCES}
  ${GMOCK_SOURCES}
)

target_include_directories(cpp_examples PRIVATE ${CMAKE_SOURCE_DIR})

#link google test libraries
target_link_libraries(cpp_examples PRIVATE gtest gtest_main gmock_main)

#include google test directories
target_include_directories(cpp_examples PRIVATE ${gtest_SOURCE_DIR})

#add precompiled header (executable must be defined first)
target_precompile_headers(cpp_examples PUBLIC pch.h)

include(GoogleTest)
gtest_discover_tests(cpp_examples)
add_test(cpp_examples cpp_examples)
