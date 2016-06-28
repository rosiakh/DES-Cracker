#include <string>
#include <stdint.h>
#include <iostream>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <ctime>

__device__ uint64_t encrypt(uint64_t plaintext, uint64_t key);

__device__ uint64_t rotate_left_28(uint64_t bits, uint32_t pos);

__device__ uint64_t rotate_right_28(uint64_t bits, uint32_t pos);

//first bit on the left is on position 1
__device__ uint32_t get_bit(uint64_t bits, uint32_t pos);

//first bit on the left is on position 1
__device__ uint64_t set_bit(uint64_t& bits, uint32_t pos, uint32_t value);

__global__ void check_keys(uint64_t plaintext, uint64_t base_key, uint64_t ciphertext, uint64_t *result, bool *is_found_key);

namespace CPU_namespace{
	uint64_t encrypt(uint64_t M, uint64_t K0);
}