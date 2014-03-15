/*
 * Author: Bucky Frost
 * File node.cpp
 * Purpose: Implementation file for the node class.
 * CS 405 Intro to A.I.
 */

#include "node.h"

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
	return uniformDistribution(generateRandomNumber);
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
	weight_m = uniformDistribution(generateRandomNumber);
}

void Node::mutateWeight()
{
	weight_m += normalDistribution(generateRandomNumber);
}

double Node::getWeight()
{
	return weight_m;
}
