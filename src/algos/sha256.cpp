#include "utility.h"
#include <cstring>

namespace sha256 {
uint32_t M[16] = {0};
uint32_t H[] = {
	0x6a09e667, 0xbb67ae85,
	0x3c6ef372, 0xa54ff53a,
	0x510e527f, 0x9b05688c,
	0x1f83d9ab, 0x5be0cd19,
}

void padMsg(std::string msg) {
        int l = msg.length();
        std::memcpy(M, msg.c_str(), l);

        char* ptr = (char*)M;
        ptr += l;
        *ptr = 0x80;
	
        ptr += (448 - l*8 + 1) / 8;
        *ptr = l*8;
}
}

int main() {
	sha256::padMsg("abc");
	util::printBin(sha256::M, 16);
}
