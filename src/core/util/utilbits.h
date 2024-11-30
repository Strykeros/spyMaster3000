#pragma once

#include <cassert>
#include <string>
#include <iostream>
#include <bitset>

//**************************************
// Util functions for printing out memory
// Memory is printed as is with no goddamn endian flipping
// #fuckstd::bitset
// *************************************

namespace utilbits {

// convert given input as a string of bits (space after each byte)
template<typename T>
std::string toString(const T* input, bool reverseEndian = false) {
    char* ptr = (char*)input;
    std::string buff;

    if (reverseEndian) {
        for (int i = sizeof(T) - 1; i >= 0; i--) {
            buff += std::bitset<8>(ptr[i]).to_string() + " ";
        }
    } else {
        for (int i = 0; i < sizeof(T); i++) {
            buff += std::bitset<8>(ptr[i]).to_string() + " ";
        }
    }
    return buff;
}

// Print given array input as bits, one element per line
template<typename T>
void printArray(const T* arr, int size, const char* msg = nullptr, bool reverseEndian = false) {
    std::string str;
    
    if(msg) {
        str += "[";
        str += msg;
        str += "]\n";
    }

    for (int i = 0; i < size; i++) {
        str += toString(&arr[i], reverseEndian) += "\n";
    }
    
    std::cout << str << std::endl;
}

// Print given input as bits in a readable format
template<typename T>
void print(T bits, const char* msg = nullptr, bool reverseEndian = false) {
    std::string str;

    if(msg) {
        str += msg;
        str += ": ";
    }
    str += toString(&bits, reverseEndian);
    std::cout << str << std::endl;
}

}

