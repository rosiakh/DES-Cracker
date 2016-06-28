#include "DES-Cracker.h"

//chosen-plaintext attack
int main()
{
	std::string plaintext = "0000000100100011010001010110011110001001101010111100110111101111";
	std::string key = "0001001100110100010101110111100110011011101111001101111111110001";

	parallel_uint64_t_version(plaintext, key);
	sequential_uint64_t_version(plaintext, key);
	bitset_version(plaintext, key);

	return 0;
}