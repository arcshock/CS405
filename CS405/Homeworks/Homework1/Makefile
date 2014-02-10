# Author: Bucky Frost
# File: Makefile
# Purpose: Makefile for CS 405
# 
CC = g++
CFLAGS =  -std=c++11 
CFLAGS_DEBUG = -Wall -g -pg
LAPTOP_OP = -march=core2 -O3 
INCLUDES = -I ./includes/
# LFLAGS
# LIBS
SRCS = ./src/*
all:
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS)  -o ./build/test.out

build-db:
	$(CC) $(CFLAGS) $(CFLAGS_DEBUG) $(INCLUDES) $(SRCS) -o ./build/debug/neuralNetDebug.out

build-laptop-op:
	$(CC) $(CFLAGS) $(LAPTOP_OP) $(INCLUDES) $(SRCS) -o ./build/release/laptopNeuralNet.out
	
