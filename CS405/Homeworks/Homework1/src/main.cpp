#include"neuralnet.h"
#include<iostream>
#include<array>
#include<chrono>
#include<ctime>

int main()
{
	std::array<int, 4> hidden_layers = {{32, 40, 10, 1}};

	NeuralNet < std::array<int, 4>::iterator > test1( hidden_layers.begin(), hidden_layers.end(), hidden_layers.size() );

	test1.setWeights();
	//test1.printNetwork();
	test1.activateNetwork();

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
	for (int i = 0; i < 11500; ++i) {
        test1.loadInput();
        test1.activateNetwork();
        //test1.printNetwork();
        //std::cout << test1.getEvalOutput() << std::endl;
	}
    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);


    std::cout << "finished computation at " << std::ctime(&end_time)


          << "elapsed time: " << elapsed_seconds.count() << "s\n";
	return 0;
}
