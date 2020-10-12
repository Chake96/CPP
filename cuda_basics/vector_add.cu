#include <cstddef>
#include <stdio.h>

namespace vecops {
	template<class T>
	__global__ 
	void adder(T* ar1, T* ar2, T* result, const std::size_t ar_size) {
		for (std::size_t index = 0; index < ar_size; index += 1) {
			//printf("Adding numbers: %d, %d\n", ar1[index], ar2[index]);
			result[index] = ar1[index] + ar2[index];
		}
	}
}