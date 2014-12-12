# File: Makefile
# Purpose: Makefile for checkers AI project
 
CC = gcc
CXX = g++
NVCC = nvcc -ccbin $(CXX) 
CXXFLAGS = -std=c++11
CPPFLAGS = -pipe
CFLAGS_DEBUG = -Wall -g 
CFLAGS_PROFILING = -pg
INCLUDES = -I ./include/
CATCH = -I ./Catch/include/
LFLAGS = -lboost_serialization

LDFLAGS = -g $(shell root-config --ldflags)
LDLIBS = $(shell root-config --libs)
SRCS = ./src/main.cpp
TESTS = ./test/unit-tests.cpp

OBJS = $(SRCS:.cpp=.o)
OBJS_TESTS = $(TESTS:.cpp=.o)

RELEASE = "./build/release/"
TEST_OUT = "./build/test/"

.PHONY: depend setup

all: setup main

main: $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJS) $(LFLAGS) -o $(RELEASE)ai 

tests: $(OBJS_TESTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJS_TESTS) $(LFLAGS) $(CATCH) -o $(TEST_OUT)test_suite
	$(TEST_OUT)test_suite

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(CATCH) -c $< -o $@

run:
	$(RELEASE)ai

setup:
	@mkdir -p ./build/{debug,release,profiling,test}

clean:
	rm -rf ./build/debug/*.*
	rm -rf ./build/release/*.*
	rm -rf ./build/profiling/*.*
	rm -rf ./includes/*.gch
	rm -rf *.o *~

depend: $(SRCS) $(TESTS)
	makedepend $(INCLUDES) $(CATCH) $^

# DO NOT DELETE THIS LINE -- make depend needs it
