CXX = g++
CXXFLAGS := -Wall -std=c++11
INC = -I./include -I./include/gtest -I./include/gtest/internal -I. -I./target/obj
OBJ_DIR = target/obj
SRC_FILES = src/gtest.cc \
		src/gtest_main.cc \
		src/gtest-death-test.cc \
		src/gtest-filepath.cc \
		src/gtest-matchers.cc \
		src/gtest-port.cc \
		src/gtest-printers.cc \
		src/gtest-test-part.cc \
		src/gtest-typed-test.cc
TEST_FILES = heap/heap.cpp
OBJ_FILES = $(patsubst %.cc, $(OBJ_DIR)/%.o, $(notdir $(SRC_FILES)))
OBJ_TEST_FILES = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(TEST_FILES)))
#GTEST_SRC_FILES = $(wildcard src/*.cc)
#GTEST_OBJ_FILES = $(wildcard src/*.obj)

GTEST_OBJ_FILES = $(wildcard target/obj/*.o)

default: build

build: $(OBJ_FILES) $(OBJ_TEST_FILES)
	mkdir -p target

$(OBJ_DIR)/%.o: heap/*.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)/%.o: src/%.cc
	mkdir -p $(OBJ_DIR)	
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@ 

link:
	ld -I$(OBJ_DIR) target/obj/gtest-typed-test.o target/obj/gtest-test-part.o target/obj/gtest-printers.o target/obj/gtest-port.o target/obj/gtest-matchers.o target/obj/gtest-filepath.o target/obj/gtest-death-test.o target/obj/gtest_main.o target/obj/gtest.o target/obj/heap.o -o target/gtest.exe
	

clean:
	rm -rf target