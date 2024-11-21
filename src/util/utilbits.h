#pragma once

#include <cassert>
#include <string>
#include <iostream>
#include <bitset>

//**************************************
// Util functions for debbuging raw bits
// *************************************

namespace utilbits {

// convert given input as a string of bits (space after each byte)
template<typename T>
std::string toString(T bits, bool reverseEndian = false) {
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
        str += toString(arr[i], reverseEndian) += "\n";
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
    str += toString(bits, reverseEndian);
    std::cout << str << std::endl;
}

}

