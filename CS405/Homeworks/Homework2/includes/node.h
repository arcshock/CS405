/*
 * Author: Bucky Frost
 * File: node.h
 * CS 405 Intro to A.I.
 * Purpose: Header file for the node class
 */

#ifndef NODE_H
#define NODE_H

#include <random>

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
	static std::mt19937 rng;
	static std::random_device rd;
	double sigmoid(double input);
	double output_m;
	double weight_m;
};

Node::Node()
{
	randomInit();
}

double Node::getOutput()
{
	return output_m;
}
double Node::randomValue()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(-1, 1);
	return dis(gen);
}

double Node::sigmoid(double input)
{
	return 2*(input/(1 + abs(input))) + 1;
}

void Node::squashOutput()
{
	output_m = sigmoid(output_m);
}

void Node::setOutput(double input)
{
	output_m = input;
}

void Node::randomInit()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(-1, 1);
	weight_m = dis(gen);
}

void Node::mutateWeight()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<> d(0, 0.25);
	weight_m += d(gen);
}

double Node::getWeight()
{
	return weight_m;
}
#endif
