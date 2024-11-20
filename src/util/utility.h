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
void printArray_asBits(const T* arr, int size, const char* msg = nullptr) {
    std::string str;
    
    if(msg) {
        str += "[";
        str += msg;
        str += "]\n";
    }

    for (int i = 0; i < size; i++) {
        std::bitset<sizeof(T) * 8> bits(arr[i]);
        for (int j = 0; j < sizeof(T) * 8; j += 8) {
            // Extract 8 bits from the bitset and convert to a string
            std::string byte = bits.to_string().substr(j, 8);
            str += byte + " ";
        }
        str += "\n";
    }
    
    std::cout << str << std::endl;
}

template<typename T>
void printBits(T bits, const char* msg = nullptr) {
    std::string str;

    if(msg) {
        str += msg;
        str += ": ";
    }

    std::string bits_str = std::bitset<sizeof(T) * 8>(bits).to_string();
    for(int i = 8; i < sizeof(T) * 8; i += 9) {
        bits_str.insert(i, " ");
    }
    str += bits_str;

    std::cout << str << std::endl;
}



template<typename T>
void printHex(const T* value, int size) {
    int Tsize = sizeof(T) / 4;
    for(int i = 0; i < size; i++) {
        std::cout << std::hex << value[i] << " "; 
    }
    std::cout << std::endl; 
}

}
