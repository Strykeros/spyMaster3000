#include <bitset>
#include <cstdint>
#include <cstring>
#include <ios>
#include <iostream>
#include <string>
#include "../util/utility.h"

namespace sha256 {
typedef uint32_t word;
typedef word block[16];

block* M;
int blockCount = 0;

uint32_t H[] = {
	0x6a09e667, 0xbb67ae85,
	0x3c6ef372, 0xa54ff53a,
	0x510e527f, 0x9b05688c,
	0x1f83d9ab, 0x5be0cd19,
};

void padMsg(std::string msg) {
        int l = msg.length() * 8;
        int k = (448 - (l + 1) % 512 + 512) % 512;
        int bitCount = l + k + 1 + 64;
        blockCount = (bitCount + 511) / 512; 
        M = new block[blockCount];

        memcpy(M, msg.c_str(), l / 8);

        uint8_t* ptr1 = (uint8_t*)M;
        ptr1 += l / 8;
        *ptr1 = 0x80;

        int* ptr2 = (int*)(M + blockCount);
        ptr2 -= 1;
        *ptr2 = __builtin_bswap32(l);
}
}

/* int main() {
	sha256::padMsg("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq");
	util::printBin(sha256::M[0], 16);
} */
