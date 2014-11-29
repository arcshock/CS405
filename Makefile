# Author: Bucky Frost
# File: Makefile
# Purpose: Makefile for checkers AI project
 
CC = g++
CFLAGS =  -std=c++11 -pipe
CFLAGS_DEBUG = -Wall -g 
CFLAGS_PROFILING = -pg
INCLUDES = -I ./include/
CATCH = -I ./Catch/include/
LFLAGS = -lboost_serialization

SRCS = ./src/*.cpp
TEST = ./test/*

# -- Usage message of Makefile
# --
# -- Ensure have directory structure created with the setup target
# --
# --

.PHONY: all clean setup build	

# -- default target: print useage message
all:
	@grep "# --" Makefile | grep -v "grep Makefile"

# -- make comp: create release executable
comp:
	$(CC) $(CFLAGS) $(LFLAGS) $(INCLUDES) $(SRCS)  -o ./build/release/checker_ai.out


# -- make run: execute release executable
run:
	./build/release/checker_ai.out


# -- make tests: build and run tests
tests:
	$(CC) $(CFLAGS) $(LFLAGS) $(CATCH) $(INCLUDES) $(TEST) -o ./build/test/test_suite.out
	./build/test/test_suite.out


# -- make debug-test: starts up gdb for the test executable
debug-test:
	$(CC) $(CFLAGS) $(CFLAGS_DEBUG) $(CATCH) $(LFLAGS) $(INCLUDES) $(TEST) -o ./build/test/test_suite_debug.out
	gdb ./build/test/test_suite_debug.out


# -- make build-db: build the debugging version of program
build-db:
	$(CC) $(CFLAGS) $(CFLAGS_DEBUG) $(INCLUDES) $(SRCS) -o ./build/debug/checker_ai.out


# -- make setup: create directory structure for building project
setup:
	mkdir -p ./build/{debug,release,profiling,test}


# -- make clean: remove all files from build directories
clean:
	rm -rf ./build/debug/*.*
	rm -rf ./build/release/*.*
	rm -rf ./build/profiling/*.*
	rm -rf ./includes/*.gch
