# Author: Bucky Frost
# File: Makefile
# Purpose: Makefile for CS 405
# 
CC = g++
CC_TAU = tau_cxx.sh
CFLAGS =  -std=c++11 
CFLAGS_DEBUG = -Wall -g -pg
INCLUDES = -I ./includes/
# LFLAGS
# LIBS

SRCS = ./src/*

LAPTOP_OPFLAGS = -march=core2 -O2 
LAPTOP_OP = laptopNeuralNet.out

DESKTOP_OPFLAGS = -march=corei7 -O2
DESKTOP_OP = desktopNeuralNet.out

all:
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS)  -o ./build/debug/test-build.out
run:
	./build/debug/test-build.out

build-db:
	$(CC) $(CFLAGS) $(CFLAGS_DEBUG) $(INCLUDES) $(SRCS) -o ./build/debug/neuralNetDebug.out

build-laptop-op:
	$(CC) $(CFLAGS) $(LAPTOP_OPFLAGS) $(INCLUDES) $(SRCS) -o ./build/release/laptopNeuralNet.out

run-laptop-op:
	./build/release/laptopNeuralNet.out
	
build-desktop-op:
	$(CC) $(CFLAGS) $(DESKTOP_OPFLAGS) $(INCLUDES) $(SRCS) -o ./build/release/desktopNeuralNet.out

run-desktop-op:
	./build/release/desktopNeuralNet.out

tau:
	$(CC_TAU) $(CFLAGS) $(INCLUDES) $(SRCS)	-o ./build/profiling/tau_build.out
	./build/profiling/tau_build.out
	mv main.* ./build/profiling/	# Need to read doc on handling object files
	mv profile.* ./build/profiling/

tau-feedforward:
	$(CC_TAU) $(CFLAGS) $(INCLUDES) ./test/feedforward.cpp -o ./build/profiling/tau_feedForward.out #need to read on passing a filename
	./build/profiling/tau_feedForward.out
	mv feedforward.* ./build/profiling/	# Need to read doc on handling object files
	mv profile.* ./build/profiling/

graph:	
	$(CC) $(CFLAGS) $(INCLUDES) ./test/graphFeedforward.cpp -o ./build/debug/graphing.out
	
# TODO pass in the test cpp files by cli argument?
#%: %.cpp
#	$(CC_TAU) -o $@ $< $(CFLAGS) $(INCLUDES)
	
clean:
	rm -rf ./build/debug/*.*
	rm -rf ./build/release/*.*
	rm -rf ./build/profiling/*.*
	rm -rf ./includes/*.gch
