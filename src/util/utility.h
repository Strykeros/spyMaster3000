#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <iostream>
#include <bitset>


namespace util{
typedef uint64_t word; //64 bit data type
typedef char byte; 

std::vector<word> stringToChunks(const char* input);
std::string chunksToString(const std::vector<uint64_t>& chunks);
void printEncryptedChunks(const std::vector<word>& chunks);

// TEMPLATES
template<typename T>
void printBits(const T* bits, int bitCount) {
    uint8_t* ptr = (uint8_t*)bits;
    int byteCount = bitCount / 8;
    for(int i = 0; i < byteCount; i++) {
        std::cout << std::bitset<8>(*(ptr+i));
        if(i % 4 == 3) std::cout << std::endl;
        else std::cout << " ";
    }
    std::cout << std::endl;
}
}
