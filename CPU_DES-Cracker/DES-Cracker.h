#include <bitset>

std::bitset<64> encrypt(std::bitset<64> M, std::bitset<64> K);

template <typename T>
void print_bitset(T bitset, int bits, std::string label);