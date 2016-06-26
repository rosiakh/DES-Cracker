#include <bitset>
#include <string>
#include <iostream>
#include <stdint.h>
#include <ctime>
#include "DES-Cracker.h"

//chosen-plaintext attack
int main()
{
	//from http://billstclair.com/grabbe/des.htm
	std::string ps("0000000100100011010001010110011110001001101010111100110111101111");
	//std::string ks("0001001100110100010101110111100110011011101111001101111111110001");
	std::string ks("0000000000000100000000000000000000000000000000000000000000000000");

	reverse(ps.begin(), ps.end());
	reverse(ks.begin(), ks.end());

	std::bitset<64> plaintext(ps);
	std::bitset<64> key(ks);
	std::bitset<64> ciphertext = encrypt(plaintext, key);
	
	uint64_t key_generator = 0;
	std::bitset<64> try_key = key_generator;

	clock_t start;
	double duration;

	start = clock();
	while (encrypt(plaintext, try_key) != ciphertext)
	{
		try_key = key_generator++;
		if (key_generator % 1000 == 0)
			std::cout << "\rChecked keys: " + std::to_string(key_generator);
	}
	std::cout << std::endl;
	
	duration = (clock() - start) / static_cast<double>(CLOCKS_PER_SEC);
	std::cout << "Time of brute force attack " << duration << " s\n";

	return 0;
}