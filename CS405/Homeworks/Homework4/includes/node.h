/*
 * Author: Bucky Frost
 * File: node.h
 * CS 405 Intro to A.I.
 * Purpose: Header file for the node class
 */

#ifndef NODE_H
#define NODE_H

#include <random>

static std::random_device rd;
static std::mt19937 rng;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<> dis(-1, 1); //interval [-1, 1), need to change?
static std::normal_distribution<> d(0, 0.12);

class Node {
public:
	Node();
	void randomInit();
	void mutateWeight();
	double getWeight();
	double getOutput();
	void squashOutput();
	void setOutput(double input);
	double randomValue();
private:
	double sigmoid(double input);
	double output_m;
	double weight_m;
};
#endif /*NODE_H*/
