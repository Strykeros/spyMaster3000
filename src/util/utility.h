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
std::string toBits_asStr(T bits, bool reverseEndian = false) {
    std::string str = std::bitset<sizeof(T) * 8>(bits).to_string();

    if(reverseEndian) {
        std::string reversed;
        for(int i = sizeof(T)*8-8; i >= 0 ; i -= 8) {
            reversed += str.substr(i, 8);
        }
        str = reversed;
    }
    
    // Add space after each byte
    for(int i = 8; i < sizeof(T) * 8; i += 9) {
        str.insert(i, " ");
    }

    return str;
}

template<typename T>
void printArray_asBits(const T* arr, int size, const char* msg = nullptr, bool reverseEndian = false) {
    std::string str;
    
    if(msg) {
        str += "[";
        str += msg;
        str += "]\n";
    }

    for (int i = 0; i < size; i++) {
        str += toBits_asStr(arr[i], reverseEndian) += "\n";
    }
    
    std::cout << str << std::endl;
}

template<typename T>
void printBits(T bits, const char* msg = nullptr, bool reverseEndian = false) {
    std::string str;

    if(msg) {
        str += msg;
        str += ": ";
    }
    str += toBits_asStr(bits, reverseEndian);
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
