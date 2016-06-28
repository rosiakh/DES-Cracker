#include "DES-Cracker.cuh"

#define THREADS_PER_BLOCK 1024
#define NUM_BLOCKS 32

//print bits in positions from 1 to pos
void print_uint64_t(uint64_t bits, uint32_t pos, std::string label)
{
	std::cout << label << ": ";
	for (int i = 1; i <= pos; ++i)
	{
		std::cout << ((bits >> (64 - i)) & 0x01);
	}
	std::cout << std::endl;
}

int main()
{
	std::string plaintext_string = "0000000100100011010001010110011110001001101010111100110111101111";
	std::string key_string = "0000000000000000000000000000000000000000001111110100000000000000";

	dim3 threads_per_block(THREADS_PER_BLOCK);
	dim3 num_blocks(NUM_BLOCKS);

	uint64_t plaintext = strtoll(plaintext_string.c_str(), nullptr, 2);
	uint64_t key = strtoll(key_string.c_str(), nullptr, 2);
	uint64_t ciphertext = CPU_namespace::encrypt(plaintext, key);

	uint64_t base_try_key = 0LL;
	uint64_t keys_tried = 0LL;

	//variables for communication with GPU
	bool is_key_found = false, *d_is_key_found;
	uint64_t result_key, *d_result_key;

	cudaMalloc(&d_is_key_found, sizeof(bool));
	cudaMalloc(&d_result_key, sizeof(uint64_t));
	cudaMemset(d_is_key_found, 0, sizeof(bool));
	cudaMemset(d_result_key, 0, sizeof(uint64_t));


	std::cout << "CUDA version:\n\n";

	clock_t start;
	double duration;

	start = clock();
	while (true)
	{
		check_keys << <num_blocks, threads_per_block >> >(plaintext, base_try_key, ciphertext, d_result_key, d_is_key_found);
		keys_tried += NUM_BLOCKS*THREADS_PER_BLOCK;
		base_try_key += NUM_BLOCKS*THREADS_PER_BLOCK;
		
		std::cout << "\rKeys tried: " << keys_tried;

		cudaMemcpy(&is_key_found, d_is_key_found, sizeof(bool), cudaMemcpyDeviceToHost);
		if (is_key_found)
		{
			cudaMemcpy(&result_key, d_result_key, sizeof(uint64_t), cudaMemcpyDeviceToHost);
			break;
		}
	}
	duration = (clock() - start) / static_cast<double>(CLOCKS_PER_SEC);
	std::cout << "\rKeys tried: " << ++keys_tried << std::endl;
	std::cout << "Time of brute force attack: " << duration << " s\n";
	print_uint64_t(result_key, 64, "Key found");

	std::cout << std::endl;
}
