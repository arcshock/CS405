#include<neuralnet.h>
#include<iostream>
#include<array>

int main()
{
	std::array<int, 4> hidden_layers = {{32, 40, 10, 1}};
	
	NeuralNet < std::array<int, 4>::iterator > test1( hidden_layers.begin(), hidden_layers.end(), hidden_layers.size() );
	
	test1.setWeights();
	test1.printNetwork();
	
	return 0;
}
