#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <iostream>
#include <bitset>

// MACROS
#define PRINTBIN(printable, len) { \
    std::bitset<len> bits(printable); \
    std::string binaryString = bits.to_string(); \
    for (size_t i = 0; i < binaryString.length(); i += 8) { \
        std::cout << binaryString.substr(i, 8) << ' '; \
    } \
    std::cout << std::endl; \
}
#define PRINTHEX(printable) std::cout << std::hex << printable << std::endl

namespace util{
typedef uint64_t word; //64 bit data type
typedef char byte; 

std::vector<word> stringToChunks(const char* input);
std::string chunksToString(const std::vector<uint64_t>& chunks);
void printEncryptedChunks(const std::vector<word>& chunks);
void printBin(uint32_t* ptr, int size);
}
