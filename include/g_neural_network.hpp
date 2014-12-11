#ifndef G_NEURAL_NETWORK_HPP
#define G_NEURAL_NETWORK_HPP
/*
 * Author: Bucky Frost
 * File: neural_network.hpp
 * Purpose: Header file for the neural network.
 */

#include <vector>
using std::vector;
#include <fstream>
#include </opt/nvidia/cuda/include/cuda.h>
#include "network_node.hpp"
#include "player.hpp"

class G_Neural_Network : public Player
{
public:

	G_Neural_Network(vector<int> network_specifications): Player(' ', "unknown")
	{
		int network_layers = network_specifications.size();

		for (int ii = 0; ii < network_layers; ++ii) 
                {
			_network.emplace_back(vector<network_node>(network_specifications[ii]));
		}
	}

        // Allocate instances in unified memory
        void *operator new(size_t len) 
        {
            void *ptr;
            cudaMallocManaged(&ptr, len);
            return ptr;
        }
        void *operator new[](size_t size)
        {
            void *ptr;
            cudaMallocManaged(&ptr, size);
            return ptr;
        }
        void operator delete(void *ptr) { cudaFree(ptr); }
        void operator delete[](void *ptr) { cudaFree(ptr); }

	// Feed forward the network to evaluate the checker board.
	float network_evaluate(vector<float> & board_input)
	{
		float evaluation_value = 0.0;
		int network_input_size = _network[0].size();
		int input_layer = 0;

                for (int ii = 0; ii < network_input_size; ++ii) 
                {
                    _network[input_layer][ii].set_input(board_input[ii]);
                }

                for (int layer = input_layer + 1; layer < _network.size(); ++layer) 
                {
                    for (int column = 0; column < _network[layer].size(); ++column) 
                    {
                        for (int ii = 0; ii < _network[layer - 1].size(); ++ii)
                            _network[layer][column]._input *=
                                    sigmoid(_network[layer - 1][ii].node_value());
                    }
                }

		auto network_output = _network.back();
		evaluation_value = _network.back().back().node_value();
		return sigmoid(evaluation_value);
	}

	bool operator==(const G_Neural_Network & other) const { return other._network == _network; }
	bool operator!=(const G_Neural_Network & other) const { return !(*this == other); }

private:
	vector<vector<network_node>> _network;

	G_Neural_Network() = default;
	friend class boost::serialization::access;
	float sigmoid(float input) { return input/(1.0 + abs(input)); }
};

__global__ void evaluate(G_Neural_Network * data)
{
    int idx = threadIdx.x;
    //data[idx] = sigmoid(stuff, stuff);
}

#endif /*NEURAL_NETWORK_HPP*/



