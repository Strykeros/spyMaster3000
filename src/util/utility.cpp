#include <cstdint>
#include <cstring> // For std::memcpy
#include "utility.h"
#include <iostream>
#include <ostream>

namespace util {
std::vector<word> stringToChunks(const char* input) {
    size_t len = std::strlen(input); // Get length of the input string
    size_t paddedLength = ((len + 7) / 8) * 8; // Calculate the required length divisible by 8
    std::vector<word> chunks; // Vector to hold 64-bit chunks

    // Create a temporary buffer of required size
    char* buffer = new char[paddedLength];
    std::memset(buffer, ' ', paddedLength); // Initialize with space characters
    std::memcpy(buffer, input, len); // Copy the input into buffer

    // Convert each 8 bytes into a single 64-bit chunk
    for (size_t i = 0; i < paddedLength; i += 8) {
        word chunk = 0;
        std::memcpy(&chunk, buffer + i, 8); // Copy 8 bytes into a 64-bit variable
        chunks.push_back(chunk); // Store in the vector
    }

    delete[] buffer; // Free the allocated memory
    return chunks; // Return the chunks
}

std::string chunksToString(const std::vector<word>& chunks) {
    std::string result;

    // Process each 64-bit chunk
    for (const auto& chunk : chunks) {
        char buffer[8]; // Temporary buffer to hold 8 characters
        std::memcpy(buffer, &chunk, 8); // Copy 8 bytes from the 64-bit chunk to the buffer
        result.append(buffer, 8); // Append the 8 characters to the result string
    }

    // Remove trailing space characters (from padding)
    while (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }

    return result; // Return the final string
}

void printEncryptedChunks(const std::vector<word>& chunks) {
    std::cout << "Encrypted: ";
    for(const auto& chunk : chunks) {
        std::cout << std::hex << chunk << " ";
    }
    std::cout << std::endl;
}

void printBin(uint32_t* ptr, int size) {
    for(int i = 0; i < size; i++) {
        const int size = sizeof(uint32_t)*8;
        std::bitset<size> bits(ptr[i]);
        std::string str = bits.to_string(); 
        for(int j = size; j >= 0; j-=8) {
            std::cout << str.substr(j, 8) << " ";
        }
        std::cout << std::endl;
    }
}
}
