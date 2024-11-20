#pragma once

#include <cassert>
#include <cstdint>
#include <iomanip>
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


/**
 * @brief A utility function to debug-print bits in a nicer way than std::bitset.
 * 
 * This function prints the binary representation of a value pointed to by `bits`. 
 * It supports optional parameters for adding a debug message and reversing the bit order.
 * 
 * @tparam T The type of the value to be printed (e.g., uint8_t, uint16_t).
 * @param bits A pointer to the value whose bits are to be printed.
 * @param bitCount The number of bits to print from the value.
 * @param msg (Optional) A debug message to print before the binary representation.
 *            Default is `nullptr`.
 * @param reverseEndian (Optional) If set to `true`, prints the bits in reverse-endian order.
 *                      Default is `false`.
 */
template<typename T>
void printBits(const T* bits, int bitCount, const char* msg = nullptr, bool reverseEndian = false) {
    uint8_t* ptr = (uint8_t*)bits;
    int byteCount = bitCount / 8;
    int Tsize = sizeof(T);
    int j = 0;

    if(msg != nullptr) {
        std::cout << msg;
        byteCount > 4 ? std::cout << "\n" : std::cout << ": ";
    }

    for(int i = 0; i < byteCount; i++) {
        if(reverseEndian) {
            if(i % Tsize == 0) j = Tsize-1;
            else j -= 2;
        }
        std::cout << std::bitset<8>(*(ptr+i+j));
        if(i % 4 == 3 && i != byteCount-1) std::cout << std::endl;
        else std::cout << " ";
    }
    std::cout << std::endl;
}
}

template<typename T>
void printHex(const T* value, int size) {
    int Tsize = sizeof(T) / 4;
    for(int i = 0; i < size; i++) {
        std::cout << std::hex << value[i] << " "; 
    }
    std::cout << std::endl; 
}
