#pragma once

#include <cassert>
#include <cstdint>
#include <string>
#include <vector>

namespace util{
typedef uint64_t word; //64 bit data type
typedef char byte; 

std::vector<word> stringToChunks(const char* input);
std::string chunksToString(const std::vector<uint64_t>& chunks);
void printEncryptedChunks(const std::vector<word>& chunks);

}
