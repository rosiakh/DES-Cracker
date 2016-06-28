#include <bitset>
#include <string>
#include <iostream>
#include <stdint.h>
#include <ctime>
#include <ppl.h>
#include <windows.h>
#include <concurrent_vector.h>

//bitset
template <typename T>
void print_bitset(T bitset, int bits, std::string label);

inline std::bitset<28> rotate_left28(std::bitset<28> b, unsigned m);

inline std::bitset<28> rotate_right28(std::bitset<28> b, unsigned m);

std::bitset<64> encrypt(std::bitset<64> M, std::bitset<64> K);

//uint64_t
void print_uint64_t(uint64_t bits, uint32_t pos, std::string label, uint32_t space = 4);

inline uint64_t rotate_left_28(uint64_t bits, uint32_t pos);

inline uint64_t rotate_right_28(uint64_t bits, uint32_t pos);

//first bit on the left is on position 1
inline uint32_t get_bit(uint64_t bits, uint32_t pos);

//first bit on the left is on position 1
inline uint64_t set_bit(uint64_t& bits, uint32_t pos, uint32_t value);

uint64_t encrypt(uint64_t M, uint64_t K0);

uint64_t encrypt_no_permutations(uint64_t M, uint64_t K0);

//Experiment
void sequential_uint64_t_version(std::string plaintext_string, std::string key_string);

//using Parallel Patterns Library
void parallel_uint64_t_version(std::string plaintext_string, std::string key_string);

void bitset_version(std::string plaintext, std::string key);