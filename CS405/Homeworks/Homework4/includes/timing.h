/*
 * Author: Bucky Frost
 * File: timing.cpp
 * Purpose: Header file for the timing functionalilty
 * CS 405 Intro to A.I.
 */

#ifndef TIMING_HPP
#define TIMING_HPP

#include "neuralnet.h"
#include "board.h"
#include <iostream>
#include <array>
#include <chrono>
#include <string>
#include <future>
#include <functional> 

std::string timingManager(int iterations, std::function<void()> functionReference);
double timingFunc(int iterations, std::function<void()> functionReference); // used for timing board evals
double timeavg(std::vector<double>::iterator begin, std::vector<double>::iterator end, int samples);
void messaging(std::string message);

void testFunction(std::function<void()> functionReference);
#endif /*TIMING_HPP*/
