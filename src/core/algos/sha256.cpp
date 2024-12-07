#include <cassert>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>
#include "sha256.h"
#include "../../util/memdebug.h"

namespace sha256 {
typedef uint32_t word; // word = 32 bits
typedef word block[16]; // block = 16 words or 512 bits

block* M;
int N;

const word H0[] = {
	0x6a09e667, 0xbb67ae85,
	0x3c6ef372, 0xa54ff53a,
	0x510e527f, 0x9b05688c,
	0x1f83d9ab, 0x5be0cd19,
};

const uint8_t  _k[64][4] = {
    {0x42, 0x8a, 0x2f, 0x98},
    {0x71, 0x37, 0x44, 0x91},
    {0xb5, 0xc0, 0xfb, 0xcf},
    {0xe9, 0xb5, 0xdb, 0xa5},
    {0x39, 0x56, 0xc2, 0x5b},
    {0x59, 0xf1, 0x11, 0xf1},
    {0x92, 0x3f, 0x82, 0xa4},
    {0xab, 0x1c, 0x5e, 0xd5},
    {0xd8, 0x07, 0xaa, 0x98},
    {0x12, 0x83, 0x5b, 0x01},
    {0x24, 0x31, 0x85, 0xbe},
    {0x55, 0x0c, 0x7d, 0xc3},
    {0x72, 0xbe, 0x5d, 0x74},
    {0x80, 0xde, 0xb1, 0xfe},
    {0x9b, 0xdc, 0x06, 0xa7},
    {0xc1, 0x9b, 0xf1, 0x74},
    {0xe4, 0x9b, 0x69, 0xc1},
    {0xef, 0xbe, 0x47, 0x86},
    {0x0f, 0xc1, 0x9d, 0xc6},
    {0x24, 0x0c, 0xa1, 0xcc},
    {0x2d, 0xe9, 0x2c, 0x6f},
    {0x4a, 0x74, 0x84, 0xaa},
    {0x5c, 0xb0, 0xa9, 0xdc},
    {0x76, 0xf9, 0x88, 0xda},
    {0x98, 0x3e, 0x51, 0x52},
    {0xa8, 0x31, 0xc6, 0x6d},
    {0xb0, 0x03, 0x27, 0xc8},
    {0xbf, 0x59, 0x7f, 0xc7},
    {0xc6, 0xe0, 0x0b, 0xf3},
    {0xd5, 0xa7, 0x91, 0x47},
    {0x06, 0xca, 0x63, 0x51},
    {0x14, 0x29, 0x29, 0x67},
    {0x27, 0xb7, 0x0a, 0x85},
    {0x2e, 0x1b, 0x21, 0x38},
    {0x4d, 0x2c, 0x6d, 0xfc},
    {0x53, 0x38, 0x0d, 0x13},
    {0x65, 0x0a, 0x73, 0x54},
    {0x76, 0x6a, 0x0a, 0xbb},
    {0x81, 0xc2, 0xc9, 0x2e},
    {0x92, 0x72, 0x2c, 0x85},
    {0xa2, 0xbf, 0xe8, 0xa1},
    {0xa8, 0x1a, 0x66, 0x4b},
    {0xc2, 0x4b, 0x8b, 0x70},
    {0xc7, 0x6c, 0x51, 0xa3},
    {0xd1, 0x92, 0xe8, 0x19},
    {0xd6, 0x99, 0x06, 0x24},
    {0xf4, 0x0e, 0x35, 0x85},
    {0x10, 0x6a, 0xa0, 0x70},
    {0x19, 0xa4, 0xc1, 0x16},
    {0x1e, 0x37, 0x6c, 0x08},
    {0x27, 0x48, 0x77, 0x4c},
    {0x34, 0xb0, 0xbc, 0xb5},
    {0x39, 0x1c, 0x0c, 0xb3},
    {0x4e, 0xd8, 0xaa, 0x4a},
    {0x5b, 0x9c, 0xca, 0x4f},
    {0x68, 0x2e, 0x6f, 0xf3},
    {0x74, 0x8f, 0x82, 0xee},
    {0x78, 0xa5, 0x63, 0x6f},
    {0x84, 0xc8, 0x78, 0x14},
    {0x8c, 0xc7, 0x02, 0x08},
    {0x90, 0xbe, 0xff, 0xfa},
    {0xa4, 0x50, 0x6c, 0xeb},
    {0xbe, 0xf9, 0xa3, 0xf7},
    {0xc6, 0x71, 0x78, 0xf2},
};

word* K = (word*)_k;

/* void padMsg(std::string msg) {
    assert(msg.length() <= 16);

    // let me cook, bro, let me cook
    M = new block[1];
    int msg_len = msg.length();
    uint8_t* M_ptr = (uint8_t*)M;
    uint8_t* msg_ptr = ((uint8_t*)msg.c_str());
    for(int i = 0; i < msg_len; i++) {
       *(M_ptr + i) = *(msg_ptr + msg_len - 1 - i);
    }
    *(M_ptr + msg_len) = 0x80;
    
    *(M_ptr + 15*8) = msg_len;
} */
void padMsg(std::string msg) {
    int l = msg.length() * 8;
    int k = (448 - (l + 1) % 512 + 512) % 512;
    int bitCount = l + k + 1 + 64;
    N = (bitCount + 511) / 512; 
    M = new block[N];

    memcpy(M, msg.c_str(), l / 8);

    uint8_t* ptr1 = (uint8_t*)M;
    ptr1 += l / 8;
    *ptr1 = 0x80;

    int* ptr2 = (int*)(M + N);
    ptr2 -= 1;
    // must swap (mirror) bits cuz the spec says so
    // *ptr2 = __builtin_bswap32(l);
    *ptr2 = l;
}

word ch(word x, word y, word z) { return (x & y) ^ (x & z); }
word maj(word x, word y, word z) { return (x & y) ^ (x & z) ^ (y & z); }
word rotr(word x, uint8_t n) { return (x >> n) | (x  << (32 - n)); }
word rotl(word x, uint8_t n) { return (x << n) | (x  >> (32 - n)); }
word sigma0(word x) { return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22); }
word sigma1(word x) { return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25); }
word smallSigma0(word x) { return rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3); }
word smallSigma1(word x) { return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10); }

void prepareMsgSchedule(word* W, block* m) {
    memcpy(W, *m, sizeof(block));
    for(int t = 16; t < 64; t++) {
        /* if(t == 17) {
            util::printBits(smallSigma1(W[t-2]), "smallSigma1 W15");
            util::printBits(W[t-2], "W15");
        } */
        W[t] =  W[t-16] + smallSigma0(W[t-15]) + W[t-7] + smallSigma1(W[t-2]);
    }    
}
digest hash(std::string msg) {
    padMsg(msg);

    digest H; // return value
    memcpy(&H, H0, sizeof(H0));

    for(int i = 0; i < N; i++) {
        // Prepare message schedule W
        word W[64];
        prepareMsgSchedule(W, &M[i]);

        // Intialize 8 working variables
        word a=H[0], b=H[1], c=H[2], d=H[3], e=H[4], f=H[5], g=H[6], h=H[7];

        // Main hashing logic
        for(int t = 0; t < 64; t++) {
            word T1 = h + sigma1(e) + ch(e,f,g) + K[t] + W[t];
            word T2 = sigma0(a) + maj(a,b,c);
            h = g;
            g = f;
            f = e;
            e = d + T1;
            d = c;
            c = b;
            b = a;
            a = T1 + T2;
        }

        // Compute intermediate hash values
        H[0] = a + H[0];
        H[1] = b + H[1];
        H[2] = c + H[2];
        H[3] = d + H[3];
        H[4] = e + H[4];
        H[5] = f + H[5];
        H[6] = g + H[6];
        H[7] = h + H[7];
    }

    return H; 
}
}
/* using namespace sha256;
#include "../../tests/fixture_sha256.cpp"
int main() {
    padMsg("abc");
    word W[64];
    prepareMsgSchedule(W, &M[0]);
    for(int i = 0; i < 64; i++) {
        std::cout << "[w " << i << "]\n";
        memdebug::print(W[i], "got");
        memdebug::print(expected_W[i], "exp");
        std::cout << "\n";

        if(i >= 16) {
            std::cout << "w" << i - 2 << ": ";
            memdebug::print(W[i-2]);

            std::cout << "w" << i - 7 << ": ";
            memdebug::print(W[i-7]);

            std::cout << "w" << i - 15 << ": ";
            memdebug::print(W[i-15]);

            std::cout << "w" << i - 16 << ": ";
            memdebug::print(W[i-16]);

            std::cout << "\n";
        }
        
    }
} */

using namespace sha256;
#include "../../../tests/fixture_sha256.cpp"
int main() {
    padMsg("abc");
    word* fuck = (word*)M;

    word W[64];
    prepareMsgSchedule(W, &M[0]);

    MemDebugger<word> mem("hex");

    for(int i = 0; i < 64; i++) {
        std::cout << "W" << i << "\n";
        mem.compare(W[i], expected_W[i], false, true);
    }
}
