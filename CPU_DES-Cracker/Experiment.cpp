#include "DES-Cracker.h"

void bitset_version(std::string plaintext, std::string key)
{
	reverse(plaintext.begin(), plaintext.end());
	reverse(key.begin(), key.end());

	std::bitset<64> plaintext_bitset(plaintext);
	std::bitset<64> key_bitset(key);
	std::bitset<64> ciphertext_bitset = encrypt(plaintext_bitset, key_bitset);

	uint64_t bitset_key_generator = 0LL;
	std::bitset<64> try_key_bitset = bitset_key_generator;

	std::cout << "Bitset version:\n\n";

	clock_t start_bitset;
	double duration_bitset;

	start_bitset = clock();

	while (encrypt(plaintext_bitset, try_key_bitset) != ciphertext_bitset)
	{
		try_key_bitset = ++bitset_key_generator;
		if (bitset_key_generator % 1000 == 0)
			std::cout << "\rKeys tried: " + std::to_string(bitset_key_generator);
	}

	duration_bitset = (clock() - start_bitset) / static_cast<double>(CLOCKS_PER_SEC);
	std::cout << "\rKeys tried: " << bitset_key_generator << std::endl;
	std::cout << "Time of brute force attack: " << duration_bitset << " s\n";
	std::cout << "Key found: ";
	for (int i = 0; i < 64; ++i)
	{
		std::cout << try_key_bitset[i];
	}
	std::cout << std::endl;

	std::cout << std::endl;
}

//using Parallel Patterns Library
void parallel_uint64_t_version(std::string plaintext_string, std::string key_string)
{
	uint64_t plaintext = strtoll(plaintext_string.c_str(), nullptr, 2);
	uint64_t key = strtoll(key_string.c_str(), nullptr, 2);
	uint64_t ciphertext = encrypt(plaintext, key);

	uint64_t try_key = 0LL;
	uint64_t keys_tried = 0LL;

	std::cout << "Parallel uint64 version:\n\n";

	clock_t start;
	double duration;

	start = clock();

	Concurrency::task_group tg;
	uint64_t upper_bound = UINT64_MAX;

	Concurrency::task_group_status status = tg.run_and_wait([&]
	{
		Concurrency::parallel_for(uint64_t(0), upper_bound, [&](uint64_t p_try_key)
		{
			if (encrypt(plaintext, p_try_key) == ciphertext)
			{
				try_key = p_try_key;
				tg.cancel();
			}
			if (++keys_tried % 1000 == 0)
				std::cout << "\rKeys tried: " + std::to_string(keys_tried);
		});
	});

	duration = (clock() - start) / static_cast<double>(CLOCKS_PER_SEC);
	std::cout << "\rKeys tried: " << ++keys_tried << std::endl;
	std::cout << "Time of brute force attack: " << duration << " s\n";
	print_uint64_t(try_key, 64, "Key found");

	std::cout << std::endl;
}

void sequential_uint64_t_version(std::string plaintext_string, std::string key_string)
{
	uint64_t plaintext = strtoll(plaintext_string.c_str(), nullptr, 2);
	uint64_t key = strtoll(key_string.c_str(), nullptr, 2);
	uint64_t ciphertext = encrypt(plaintext, key);

	uint64_t try_key = 0LL;
	uint64_t keys_tried = 0LL;

	std::cout << "Sequential uint64 version:\n\n";

	clock_t start;
	double duration;

	start = clock();

	for (; encrypt(plaintext, try_key) != ciphertext; ++try_key)
	{
		if (try_key % 1000 == 0)
			std::cout << "\rKeys tried: " + std::to_string(try_key);
	}
	keys_tried = try_key;

	duration = (clock() - start) / static_cast<double>(CLOCKS_PER_SEC);
	std::cout << "\rKeys tried: " << ++keys_tried << std::endl;
	std::cout << "Time of brute force attack: " << duration << " s\n";
	print_uint64_t(try_key, 64, "Key found");

	std::cout << std::endl;
}