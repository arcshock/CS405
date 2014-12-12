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

LDFLAGS=-g $(shell root-config --ldflags)
LDLIBS=$(shell root-config --libs)
SRCS = ./src/main.cpp
TEST = ./test/*

OBJS=$(SRCS:.cpp=.o)

RELEASE ="./build/release/"


.PHONY: depend setup

all:setup main

main: $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(RELEASE)ai $(OBJS) $(LFLAGS)
.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<  -o $@

run:
	./build/release/checker_ai.out


unit-tests:
	$(CC) $(CFLAGS) $(LFLAGS) $(CATCH) $(INCLUDES) $(TEST) -o ./build/test/test_suite.out
	./build/test/test_suite.out

setup:
	@mkdir -p ./build/{debug,release,profiling,test}

clean:
	rm -rf ./build/debug/*.*
	rm -rf ./build/release/*.*
	rm -rf ./build/profiling/*.*
	rm -rf ./includes/*.gch
	rm -rf *.o *~

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
