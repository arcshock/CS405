#ifndef NEURAL_NET_H
#define NEURAL_NET_H
/*
 * Author: Bucky Frost
 * File: neuralnet.h
 * CS 405 Intro to A.I.
 * Purpose: Header of neural network class.
 * Date: 2014-01-27
 */

const unsigned int INPUT_NODE_NUM = 32;
const unsigned int HID_L0_NODE_NUM = 40;
const unsigned int HID_L1_NODE_NUM = 10;
const unsigned int OUTPUT_NODE_NUM = 1;

class InputNeuralNode {
public:
private:
	double m_outputVal;
	double m_input;
};
#endif //NEURAL_NET_H
