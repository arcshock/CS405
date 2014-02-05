#include<neuralnet.h>
#include<iostream>
#include<array>

int main()
{
	std::array<int, 2> hidden_layers = {{32, 40, 10, 1}};
//	NeuralNet <std::array<int, 2>::iterator>test(32, hidden_layers.begin(), hidden_layers.end(), 1);
	NeuralNet < std::array<int, 2>::iterator > test1(hidden_layers.begin(), hidden_layers.end());
	return 0;
}
