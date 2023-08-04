# Makefile for building Google Test and test files

# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++11 -I.

# Directory where Google Test source code is located
GTEST_DIR := .

# Directory where Google Test header files are located
GTEST_INC_DIR := $(GTEST_DIR)/include

# Directory where Google Test source files are located
GTEST_SRC_DIR := $(GTEST_DIR)/src

# List of Google Test source files to be compiled
GTEST_SRCS := $(GTEST_SRC_DIR)/gtest-all.cc $(GTEST_SRC_DIR)/gtest_main.cc

# Directory where the built Google Test object files will be placed
BUILD_DIR := build

# Output binary name
OUTPUT_BIN := test

# Object files to be built from Google Test source files
GTEST_OBJS := $(addprefix $(BUILD_DIR)/, $(notdir $(GTEST_SRCS:.cc=.o)))

# Directory where the test source files are located
TEST_DIR := ./threads

# List of test source files to be compiled
TEST_SRCS := $(wildcard $(TEST_DIR)/*.cpp)

# Object files to be built from test source files
TEST_OBJS := $(addprefix $(BUILD_DIR)/, $(notdir $(TEST_SRCS:.cpp=.o)))

# Default target
all: $(BUILD_DIR) $(BUILD_DIR)/$(OUTPUT_BIN)

# Rule to create the build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Rule to build Google Test object files
$(BUILD_DIR)/%.o: $(GTEST_SRC_DIR)/%.cc
	$(CXX) $(CXXFLAGS) -I$(GTEST_INC_DIR) -c $< -o $@

# Rule to build test object files
$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(GTEST_INC_DIR) -c $< -o $@

# Rule to build the test binary
$(BUILD_DIR)/$(OUTPUT_BIN): $(GTEST_OBJS) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -I$(GTEST_INC_DIR) $(GTEST_OBJS) $(TEST_OBJS) -o $@

# Clean up generated files
clean:
	rm -rf $(BUILD_DIR)

# Run the tests
test: all
	./$(BUILD_DIR)/$(OUTPUT_BIN)