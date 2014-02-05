#include<neuralnet.h>
#include<iostream>
#include<array>

int main()
{
	std::array<int, 2> hidden_layers = {{40, 10}};
	NeuralNet <int> test;// = NeuralNet <int>(32, hidden_layers.begin, hidden_layers.end, 1);
	return 0;
}
