/**
 * File: neural_network.hpp
 * Purpose: Header file for the neural network.
 */

#include <vector>
using std::vector;
#include <fstream>
#include </opt/nvidia/cuda/include/cuda.h>
#include </opt/nvidia/cuda/include/curand.h>
#include "player.hpp"
#include "checker_board.hpp"
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <random>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

static std::random_device randomDevice;
static std::mt19937 random_value(randomDevice());
static std::uniform_real_distribution<> uniform_distribution(-1, 1);

struct network_node
{
	float _input;
	float _weight;

	__host__ __device__ network_node() : _input(1.0)
	{
	//	_weight = uniform_distribution(random_value);
	}

	__host__ __device__ void set_input(float val) { _input = val; }
	__host__ __device__ float node_value() { return _input*_weight; }

	__host__ __device__ bool operator==(const network_node & other) const
	{
		return (other._input == _input && other._weight == _weight);
	}
};
#include<curand_kernel.h>


int n = 200;

__device__ float generate( curandState* globalState, int ind ) 
{
    //int ind = threadIdx.x;
    curandState localState = globalState[ind];
    float RANDOM = curand_uniform( &localState );
    globalState[ind] = localState;
    return RANDOM;
}

__global__ void setup_kernel ( curandState * state, unsigned long seed )
{
    int id = threadIdx.x;
    curand_init ( seed, id, 0, &state[id] );
}

__global__ void kernel(float* N, curandState* globalState, int n)
{
    // generate random numbers
    for(int i=0;i<40000;i++)
    {
        int k = generate(globalState, i) * 100000;
        while(k > n*n-1)
        {
            k-=(n*n-1);
        }
        N[i] = k;
    }
}

// ffrom stackoverlow
class Unified 
{
    public:
        // Allocate instances in CPU/GPU unified memory. Needs Kepler Architecture.
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

};

typedef vector<vector<network_node>> Network;
class G_Neural_Network : public Unified
{
public:

         __host__ __device__ G_Neural_Network(vector<int> network_specs) 
	{
		int network_layers = network_specs.size();

		for (int ii = 0; ii < network_layers; ++ii) 
                {
			_network.emplace_back(vector<network_node>(network_specs[ii]));
		}
	}


	// Feed forward the network to evaluate the checker board.
         __host__ __device__ void network_evaluate(float * weights)
	{
		
		int network_input_size = 32; 
		int input_layer = 0;

		thrust::device_vector<float> temp(network_input_size);

		thrust::fill(temp.begin(), temp.end(), 1.0);

                for (int ii = 0; ii < network_input_size; ++ii) 
                {
                    //_network[input_layer][ii].set_input(board_input[ii]);
                    _network[input_layer][ii].set_input(temp[ii]);
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
		float evaluation_value = _network.back().back().node_value();
		//return sigmoid(evaluation_value);
	}
/*	
	__host__ __device__  bool operator==(const G_Neural_Network & other) const 
        { return other._network == _network; }
	__host__ __device__  bool operator!=(const G_Neural_Network & other) const 
        { return !(*this == other); }
*/

private:
	Network _network;

	__host__ __device__  G_Neural_Network() = default;
	__host__ __device__  float sigmoid(float input) { return input/(1.0 + abs(input)); }
#if 0
	friend class boost::serialization::access;
	template<class Archive>
	 void serialize(Archive & ar, const unsigned int version) 
        { ar & _network; }
#endif
};

/**
 * Author: Bucky Frost
 * File: main.cpp
 * Purpose: main function for checkers AI.
 */

#include <iostream>
#include <vector>
#include <chrono>
//#include "g_neural_network.hpp"
#include "minimax.hpp"
#include "checker_board.hpp"

using std::cout;
using std::endl;
 __device__ void network_evaluate(float * weights)
{
	


}

__global__ void evaluate(float * layer0, float * layer1, float * layer2, float * layer3, float * t0, float * t1,  float *t2)
{
	// use alls threads	
	int idx = threadIdx.x + blockIdx.x * blockDim.x;
	//network_evaluate(weights); 
	*t0 = *t0 + layer0[idx];	
	*t1 = *t1 + layer1[idx];	
	*t2 = *t2 + layer2[idx];	
}

__global__ void final(float * layer3, float * t0, float * t1,  float *t2)
{
	
	int idx = threadIdx.x + blockIdx.x * blockDim.x;
	layer3[idx] = *t0 + *t1 + *t2 + layer3[idx];
}
// Precondition - It doesn't make sense to have less than 32 as first layer
// for checkers evaluations. It doesn't make sense to have more than 1 as
// final layer. Thus, those will automatically be set for any non-default
// arg parameters passed into main.
std::vector<int> argparse(int argc, char* argv[])
{
    std::vector<int> layer_sizes{32, 40, 10, 1};
    if (argc > 1)
    {
        layer_sizes.resize(argc + 1);
        layer_sizes.push_back(32);
        for (unsigned int count = 1; count < argc; ++count)
        {
            layer_sizes[count] = std::stoi(argv[count]);
        }
        layer_sizes.push_back(1);

    }
    return layer_sizes;
}


void create_NN(std::vector<int>);
void timing(std::vector<int>);

int main(int argc, char* argv[])
{
        std::vector<int> neural_network_layers = argparse(argc, argv);
	    int N=40000;

    curandState* devStates;
    cudaMalloc ( &devStates, N*sizeof( curandState ) );

    // setup seeds
    setup_kernel <<< 1, N >>> ( devStates,unsigned(time(NULL)) );

    float N2[40000];
    float* N3;


	int n1 = 50000;
	int n2 = 12500;
	int n3 = 1250;
	float nr1[n1];
	float nr2[n2];
	float nr3[n3];
	
	float* nr1_val;
	float* nr2_val;
	float* nr3_val;
    cudaMalloc((void**) &N3, sizeof(float)*N);
    cudaMalloc((void**) &nr1_val, sizeof(float)*n1);
    cudaMalloc((void**) &nr2_val, sizeof(float)*n2);
    cudaMalloc((void**) &nr3_val, sizeof(float)*n3);

//get some random values into the first param
    kernel<<<1,1>>> (N3, devStates, n);
    kernel<<<1,1>>> (nr1_val, devStates, n);
    kernel<<<1,1>>> (nr2_val, devStates, n);
    kernel<<<1,1>>> (nr3_val, devStates, n);
float tt = 1.0;
float ttu = 1.0;
float tti = 1.0;
float * t0 = &tt;
float * t1 = &ttu;
float * t2 = &tti;

	evaluate<<<1,1>>> (N3, nr1_val, nr2_val, nr3_val, t0, t1, t2);
	final<<<1,1>>> (nr3_val, t0,t1,t2);

    cudaMemcpy(nr1, nr1_val, sizeof(float)*n1, cudaMemcpyDeviceToHost);
    cudaMemcpy(nr2, nr2_val, sizeof(float)*n2, cudaMemcpyDeviceToHost);
    cudaMemcpy(nr3, nr3_val, sizeof(float)*n3, cudaMemcpyDeviceToHost);
	for ( int ii = 0; ii < n1; ++ii)
		cout << nr1[0] << endl;
	for ( int ii = 0; ii < n1; ++ii)
		cout << nr2[0] << endl;
	for ( int ii = 0; ii < n3; ++ii)
		cout << nr3[0] << endl;

/*
    for(int i=0;i<N;i++)
    {
        cout<<N2[i]<<endl;
    }
*/

     //   timing(neural_network_layers);
	return 0;
}

#if 0
void create_NN(std::vector<int> layers)
{
        G_Neural_Network * base_case_network = new G_Neural_Network(layers);

	std::ofstream ofs("test_network_save.txt");

	boost::archive::text_oarchive oa(ofs);

	oa << base_case_network;
	ofs.close();

}

void timing(std::vector<int> layers)
{
        G_Neural_Network * player = new G_Neural_Network(layers);
        int n = 0;
        for (auto i : layers) { n += i; } // sum of NN nodes.

        // Run gpu stuff on shared space
        int nBlocks = 1;    // GPU thread blocks to run
        int blockDim = n;   // threads per block, should be 256 for best performance
	for (int ii = 0; ii < 100; ++ii) {
        	auto start_gpu = std::chrono::high_resolution_clock::now();
		evaluate<<<nBlocks, blockDim>>>(player);    // evaluate on gpu
		cudaDeviceSynchronize();    // wait to finish evaluation
        	auto end_gpu = std::chrono::high_resolution_clock::now();
        	cout << std::chrono::duration<double, std::nano> (end_gpu - start_gpu).count() << endl;
	}


}
#endif
