#ifndef NODE_H
#define NODE_H
#include <random>
/*
 * Author: Bucky Frost
 * File: node.h
 * CS 405 Intro to A.I.
 * Purpose: Header file for the node class
 */

class Node {
public:
	void randomInit();
	void mutateWeight();
private:
	double bias_m;
	double weight_m;
};

void Node::randomInit()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(-1, 1);
	weight_m = dig(gen);
}

void Node::mutateWeight()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<> d(0, 0.5);
	weight_m += d(gen);
}
