/*
 * Author: Bucky Frost
 * File: node.h
 * CS 405 Intro to A.I.
 * Purpose: Header file for the node class
 */

#ifndef NODE_H
#define NODE_H

#include <random>

const double SIGMA = 0.12;
static std::random_device randomDevice;
static std::mt19937 generateRandomNumber(randomDevice());
static std::uniform_real_distribution<> uniformDistribution(-1, 1); //interval [-1, 1), need to change?
static std::normal_distribution<> normalDistribution(0, SIGMA);

class Node {
public:
	// Implementation TODO: have a function that takes in input from anouther node, have this value stored, then can call output to squash that value.
	Node();
	void randomInit();
	void mutateWeight();
	double getWeight() const;
	double getOutput() const;
	void squashOutput();
	void setOutput(double input);
	double randomValue();
private:
	double sigmoid(double input);
	double output_m;
	double weight_m;
};
#endif /*NODE_H*/
