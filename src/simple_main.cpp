#include <cuda.h>
#include <iostream>
using std::cout;
using std::endl;

class Unified {
public:
  void *operator new(size_t len) 
  {
	void *ptr;
	cudaMallocManaged(&ptr, len);
	return ptr;
  }
  void* operator new[] (std::size_t size) 
  {
	void *ptr; 
	cudaMallocManaged(&ptr,size);
	return ptr;
  }
  void operator delete(void *ptr) { cudaFree(ptr); }
  void operator delete[] (void* ptr) { cudaFree(ptr); }
};

class widget : public Unified 
{
public:
	float value;
	__device__ void setValue(float v) { value=v; }
};

__global__ void set_array(widget *w,float param) {
	int i=threadIdx.x + blockIdx.x*blockDim.x; 
	w[i].setValue(i+param);
}

int main(int argc,char *argv[]) 
{
	int n=1024;                 // total number of floats
	widget *w=new widget[n];    // shared array of n values (overloaded new[])
	int nBlocks=1;              // GPU thread blocks to run
	int blockDim=n;             // threads/block, should be 256 for best performance
	set_array<<<nBlocks,blockDim>>>(w,0.1234); /* run kernel on GPU */ 
	cudaDeviceSynchronize(); /* Wait for kernel to finish filling vals array */

	int i=7;
	std::cout<<"widget["<<i<<"] = "<<w[i].value<<"\n";
        delete [] w;
        return 0;
}
