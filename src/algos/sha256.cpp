#include <algorithm>
#include <bitset>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>
#include "sha256.h"
#include "../util/utility.h"

namespace sha256 {
typedef uint32_t word;
typedef word block[16];

block* M;
int N;

const word H0[] = {
	0x6a09e667, 0xbb67ae85,
	0x3c6ef372, 0xa54ff53a,
	0x510e527f, 0x9b05688c,
	0x1f83d9ab, 0x5be0cd19,
};

const word K[] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
};

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
    *ptr2 = __builtin_bswap32(l);
}

word ch(word x, word y, word z) { return (x & y) ^ (x & z); }
word maj(word x, word y, word z) { return (x & y) ^ (x & z) ^ (y & z); }
word rotr(word x, uint8_t n) { return (x >> n) | (x  << (32 - n)); }
word rotl(word x, uint8_t n) { return (x << n) | (x  >> (32 - n)); }
word sigma0(word x) { return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22); }
word sigma1(word x) { return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25); }
word smallSigma0(word x) { return rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3); }
word smallSigma1(word x) { return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10); }

word modoloAdd(std::vector<word> words) {
    word sum = words[0];
    for(int i = 1; i < words.size(); i++) {
        sum = (sum + words[i]) % 0x100000000;
    }
    return sum;
}

void prepareMsgSchedule(word* W, block* m) {
    memcpy(W, *m, sizeof(block));
    for(int t = 16; t < 64; t++) {
        W[t] = modoloAdd({
            smallSigma1(W[t-2]),
            W[t-7],
            smallSigma0(W[t-15]),
            W[t-16]
        });
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
            word T1 = modoloAdd({
                h,
                sigma1(e),
                ch(e,f,g),
                K[t],
                W[t]
            }); 
            word T2 = modoloAdd({
                sigma0(a),
                maj(a,b,c)
            });
            h = g;
            g = f;
            f = e;
            e = modoloAdd({d, T1});
            d = c;
            c = b;
            b = a;
            a = modoloAdd({T1, T2});
        }

        // Compute intermediate hash values
        H[0] = modoloAdd({a, H[0]});
        H[1] = modoloAdd({b, H[1]});
        H[2] = modoloAdd({c, H[2]});
        H[3] = modoloAdd({d, H[3]});
        H[4] = modoloAdd({e, H[4]});
        H[5] = modoloAdd({f, H[5]});
        H[6] = modoloAdd({g, H[6]});
        H[7] = modoloAdd({h, H[7]});
    }

    return H; 
}
}
#include "../../tests/fixture_sha256.cpp"
using namespace sha256;
int main() {
    word* W = new word[64];
    /* const word* expected =  new word[] {
	0x61626364, 0x696a6b6c,
	0x62636465, 0x6a6b6c6d,
	0x63646566, 0x6b6c6d6e,
	0x64656667, 0x6c6d6e6f,
	0x65666768, 0x6d6e6f70,
	0x66676869, 0x6e6f7071,
	0x6768696a, 0x80000000,
	0x68696a6b, 0x00000000,
    }; */

    padMsg("abc");
    // util::printBits(M[0], 512);
    // std::cout << "\n";
    //printHex(M, 16);
    //std::cout << "\n";
    prepareMsgSchedule(W, &M[0]);
    for (int i = 0; i < 64; i++) {
        std::cout << "[" << i << "]\n";
        util::printBits(&W[i], 32);
        util::printBits(&expected_W[i], 32, true);
        std::cout << "\n";
        /* std::cout << std::bitset<32>(W[i]) << "\n"; 
        std::cout << std::bitset<32>(expected_W[i]) << "\n\n";  */
    }

    /* util::printBits(&W[16], 32);
    std::cout << "Output:\n";
    printHex(M[0], 16);
    std::cout << "Expected:\n";
    printHex(expected, 16);
    delete[] W;
    delete[] expected; */
}
