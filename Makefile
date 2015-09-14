CC = gcc
CXX = g++
CXXFLAGS = -std=c++11 -pipe -Wall -g -I ./Catch/include/ -I ./include/
LFLAGS = -lboost_serialization
LDFLAGS = -g $(shell root-config --ldflags)
LDLIBS = $(shell root-config --libs)

.PHONY: setup

all: setup
	@echo ""
	@echo "Run 'make tests' to build and run test suite."

catch: ./test/catch_main.o
	$(CXX) $(LFLAGS) $(CXXFLAGS) ./test/catch_main.cpp -o ./test/catch_main.o

spec: ./test/network_spec_tests.o

checkers: ./test/checker_tests.o

tests: spec checkers
	$(CXX) $(LFLAGS) ./test/*.o -o ./build/test/test_suite
	./build/test/test_suite

setup:
	@mkdir -p ./build/test

clean:
	rm -rf ./build/test/*.*
	rm -rf ./includes/*.gch
	rm -rf ./test/*.o
	rm -rf *.o *~
