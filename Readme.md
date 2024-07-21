# cpp_examples

Project that uses cmake, gtest

## How to build

1. generate project build system 
    ```
    cmake -B build -S .
    ```
2. build project
    ```
    cmake --build build
    ```
3. runt gcov
   cd build
   make gcov