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
template<typename T>
void printBits(const T* bits, int bitCount, bool reverseEndian = false) {
    uint8_t* ptr = (uint8_t*)bits;
    int byteCount = bitCount / 8;
    int Tsize = sizeof(T);
    int j = 0;
    for(int i = 0; i < byteCount; i++) {
        if(reverseEndian) {
            if(i % Tsize == 0) j = Tsize-1;
            else j -= 2;
        }
        std::cout << std::bitset<8>(*(ptr+i+j));
        if(i % 4 == 3) std::cout << std::endl;
        else std::cout << " ";
    }
    std::cout << std::endl;
}
}

/*
    Desc: Prints hexidecimal representation for any lenght input in a formatted way
    Params:
        bits: input
        bitCount: how many bits of input to print
        digitsPerOutputChunk: output is chunks of hex digits, specify digits per chunk (OPTIONAL default = 2)
 */
/* template<typename T>
void printHex(const T* bits, int bitCount, int digitsPerOutputChunk = 2) {
    assert(bitCount % 8 == 0 && "bitCount must be divisible by 8!");
    assert(digitsPerOutputChunk % 2 == 0 && "digitsPerOutputChunk must be divisible by 2!");

    int byteCount = bitCount / 8;
    uint8_t* ptr = (uint8_t*)bits;


    for(int i = 0; i < byteCount; i++) {
        int byte = (int)ptr[i];
        if(byte == 0) std::cout << "00";
        else std::cout << std::hex << byte;
        //std::cout << "|";
        if((i + 1) % (digitsPerOutputChunk / 2) == 0) std::cout << " ";
    }

    std::cout << std::endl; 
}
*/
template<typename T>
void printHex(const T* value, int size) {
    int Tsize = sizeof(T) / 4;
    for(int i = 0; i < size; i++) {
        std::cout << std::hex << value[i] << " "; 
    }
    std::cout << std::endl; 
}
