# Author: Bucky Frost
# File: Makefile
# Purpose: Makefile for CS 405
# 
CC = g++
CFLAGS =  -std=c++11 
CFLAGS_DEBUG = -Wall -g -pg
INCLUDES = -I ./includes/
# LFLAGS
# LIBS

SRCS = ./src/*

LAPTOP_OPFLAGS = -march=core2 -O2 
LAPTOP_OP = laptopNeuralNet.out

DESKTOP_OPFLAGS = -march=corei7 -02
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

clean:
	rm -rf ./build/debug/*.*
	rm -rf ./build/release/*.*
