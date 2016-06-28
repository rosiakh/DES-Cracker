#include "DES-Cracker.h"
#define PRINT_F 0
#define PRINT_MAIN 0

const int E[48] = {
	32, 1, 2, 3, 4, 5,
	4, 5, 6, 7, 8, 9,
	8, 9, 10, 11, 12, 13,
	12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21,
	20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29,
	28, 29, 30, 31, 32, 1
};

const int P[32] = {
	16, 7, 20, 21,
	29, 12, 28, 17,
	1, 15, 23, 26,
	5, 18, 31, 10,
	2, 8, 24, 14,
	32, 27, 3, 9,
	19, 13, 30, 6,
	22, 11, 4, 25
};

const unsigned long S[8][4][16] = {
	{
		{ 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 },
		{ 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8 },
		{ 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0 },
		{ 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 }
	},
	{
		{ 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10 },
		{ 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5 },
		{ 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15 },
		{ 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 }
	},
	{
		{ 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8 },
		{ 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1 },
		{ 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7 },
		{ 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 }
	},
	{
		{ 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15 },
		{ 13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9 },
		{ 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4 },
		{ 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 }
	},
	{
		{ 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9 },
		{ 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6 },
		{ 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14 },
		{ 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 }
	},
	{
		{ 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11 },
		{ 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8 },
		{ 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6 },
		{ 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 }
	},
	{
		{ 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1 },
		{ 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6 },
		{ 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2 },
		{ 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 }
	},
	{
		{ 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7 },
		{ 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2 },
		{ 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8 },
		{ 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 }
	}
};

const int IP_tab[64] = {
	58, 50, 42, 34, 26, 18, 10, 2,
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6,
	64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17, 9, 1,
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7
};

const int IPminus[64] = {
	40, 8, 48, 16, 56, 24, 64, 32,
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30,
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28,
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26,
	33, 1, 41, 9, 49, 17, 57, 25
};

const int PC1[56] = {
	57, 49, 41, 33, 25, 17, 9,
	1, 58, 50, 42, 34, 26, 18,
	10, 2, 59, 51, 43, 35, 27,
	19, 11, 3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,
	7, 62, 54, 46, 38, 30, 22,
	14, 6, 61, 53, 45, 37, 29,
	21, 13, 5, 28, 20, 12, 4
};

const int PC2[48] = {
	14, 17, 11, 24, 1, 5,
	3, 28, 15, 6, 21, 10,
	23, 19, 12, 4, 26, 8,
	16, 7, 27, 20, 13, 2,
	41, 52, 31, 37, 47, 55,
	30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53,
	46, 42, 50, 36, 29, 32
};

const int shifts[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

//print bits in positions from 1 to pos
void print_uint64_t(uint64_t bits, uint32_t pos, std::string label, uint32_t space)
{
	std::cout << label << ": ";
	for (int i = 1; i <= pos; ++i)
	{
		std::cout << get_bit(bits, i);
		if (i % space == 0) std::cout << " ";
	}
	std::cout << std::endl;
}

inline uint64_t rotate_left_28(uint64_t bits, uint32_t pos)
{
	return bits >> (28 - pos) | bits << pos;
}

inline uint64_t rotate_right_28(uint64_t bits, uint32_t pos)
{
	return bits << (28 - pos) | bits >> pos;
}

//first bit on the left is on position 1
inline uint32_t get_bit(uint64_t bits, uint32_t pos)
{
	return (bits >> (64 - pos)) & 0x01;
}

//first bit on the left is on position 1
inline uint64_t set_bit(uint64_t& bits, uint32_t pos, uint32_t value)
{
	uint64_t mask = 1LL << (64 - pos);
	if (value)
		bits |= mask;
	else
		bits &= ~mask;
	return bits;
}

inline uint64_t f(uint64_t data, uint64_t key)
{
	int i, j;
	uint64_t E_data = 0LL;
	for (i = 1; i <= 48; ++i)
	{
		set_bit(E_data, i, get_bit(data, E[i - 1]));
	}

#if PRINT_F
	print_uint64_t(E_data, 48, "E(R)", 6);
#endif

	uint64_t result = E_data^key;

#if PRINT_F
	print_uint64_t(result, 48, "E(R)+K", 6);
#endif

	uint64_t B[8];

	for (i = 1; i <= 8; ++i)
	{
		B[i - 1] = 0LL;
		for (j = 1; j <= 6; ++j)
		{
			set_bit(B[i - 1], j, get_bit(result, (i - 1) * 6 + j));
		}

#if PRINT_F
		print_uint64_t(B[i - 1], 6, "B_" + std::to_string(i));
#endif
	}

	uint64_t SB[80];
	uint64_t temp = 0LL;
	uint32_t r, c;

	for (i = 1; i <= 8; ++i)
	{
		SB[i - 1] = 0LL;
		r = 2 * get_bit(B[i - 1], 1) + get_bit(B[i - 1], 6);
		c = 8 * get_bit(B[i - 1], 2) + 4 * get_bit(B[i - 1], 3) + 2 * get_bit(B[i - 1], 4) + get_bit(B[i - 1], 5);

		temp = S[i - 1][r][c];
		for (j = 1; j <= 4; ++j)
		{
			set_bit(SB[i - 1], j, get_bit(temp, 60 + j));
		}
	}

#if PRINT_F
	for (i = 1; i <= 8; ++i)
	{
		print_uint64_t(SB[i - 1], 4, "SB_" + std::to_string(i));
	}
#endif

	uint64_t SBconcat = 0LL;
	for (i = 1; i <= 8; ++i)
	{
		SBconcat = SBconcat << 4;
		SBconcat = SBconcat | (SB[i - 1] >> 60);
	}
	SBconcat = SBconcat << 32;

#if PRINT_F
	print_uint64_t(SBconcat, 32, "SBconcat");
#endif

	uint64_t f_res = 0LL;
	for (i = 1; i <= 32; ++i)
	{
		set_bit(f_res, i, get_bit(SBconcat, P[i - 1]));
	}

#if PRINT_F
	print_uint64_t(f_res, 32, "f_res");
#endif

	return f_res;
}

//M - plaintext; K - key
uint64_t encrypt(uint64_t M, uint64_t K0)
{
	//STEP 1: Create 16 subkeys, each of which is 48-bits long

#if PRINT_MAIN
	print_uint64_t(K0, 64, "Key", 8);
#endif

	int i, b;
	uint64_t Kplus = 0LL;
	for (i = 1; i <= 56; ++i)
	{
		set_bit(Kplus, i, get_bit(K0, PC1[i - 1]));
	}

#if PRINT_MAIN
	print_uint64_t(Kplus, 56, "K+", 7);
#endif

	uint64_t C[17], D[17];

	C[0] = 0LL;
	D[0] = 0LL;
	for (i = 1; i <= 28; ++i)
	{
		set_bit(C[0], i, get_bit(Kplus, i));
		set_bit(D[0], i, get_bit(Kplus, 28 + i));
	}

	for (i = 1; i <= 16; ++i)
	{
		C[i] = 0LL;
		D[i] = 0LL;
		C[i] = rotate_left_28(C[i - 1], shifts[i - 1]);
		D[i] = rotate_left_28(D[i - 1], shifts[i - 1]);
	}

#if PRINT_MAIN
	for (i = 0; i <= 16; ++i)
	{
		print_uint64_t(C[i], 28, "C_" + std::to_string(i));
		print_uint64_t(D[i], 28, "D_" + std::to_string(i));
	}
#endif

	uint64_t K[16];
	for (i = 1; i <= 16; ++i)
	{
		K[i - 1] = 0LL;
		for (b = 1; b <= 48; ++b)
		{
			set_bit(K[i - 1], b, PC2[b - 1] > 28 ? get_bit(D[i], PC2[b - 1] - 28) : get_bit(C[i], PC2[b - 1]));
		}
	}

#if PRINT_MAIN
	for (i = 1; i <= 16; ++i)
	{
		print_uint64_t(K[i - 1], 48, "K_" + std::to_string(i), 6);
	}
#endif

	//STEP 2: Encode each 64-bit block of data

	uint64_t IP = 0LL;
	for (i = 1; i <= 64; ++i)
	{
		set_bit(IP, i, get_bit(M, IP_tab[i - 1]));
	}

#if PRINT_MAIN
	print_uint64_t(IP, 64, "IP", 4);
#endif

	uint64_t L[17], R[17];
	L[0] = 0LL;
	R[0] = 0LL;
	for (i = 1; i <= 32; ++i)
	{
		set_bit(L[0], i, get_bit(IP, i));
		set_bit(R[0], i, get_bit(IP, 32 + i));
	}

#if PRINT_MAIN
	print_uint64_t(L[0], 32, "L_0", 4);
	print_uint64_t(R[0], 32, "R_0", 4);
#endif

	for (i = 1; i <= 16; ++i)
	{
		L[i] = 0LL;
		R[i] = 0LL;
		L[i] = R[i - 1];
		R[i] = L[i - 1] ^ f(R[i - 1], K[i - 1]);

#if PRINT_MAIN
		print_uint64_t(L[i], 32, "L_" + std::to_string(i), 4);
		print_uint64_t(R[i], 32, "R_" + std::to_string(i), 4);
#endif
	}

	uint64_t R16L16 = 0LL;
	for (i = 1; i <= 64; ++i)
	{
		set_bit(R16L16, i, i <= 32 ? get_bit(R[16], i) : get_bit(L[16], i - 32));
	}

#if PRINT_MAIN
	print_uint64_t(R16L16, 64, "R_16_L_16", 8);
#endif

	uint64_t result = 0LL;
	for (i = 1; i <= 64; ++i)
	{
		set_bit(result, i, get_bit(R16L16, IPminus[i - 1]));
	}

#if PRINT_MAIN
	print_uint64_t(result, 64, "IP-1", 8);
#endif

	return result;
}