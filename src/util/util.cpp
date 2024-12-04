#include <cassert>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>
#include "util.h"

namespace util {

std::string strToHex(std::string str) {
	std::ostringstream output;
	for (unsigned char c : str)
		output << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
	return output.str();
}

std::string hexToASCII(std::string hex) {
	if(hex.length() % 2 != 0) throw std::invalid_argument("Missing hex digit");

	std::string output;
	std::string buff;
	for(int i = 0; i < hex.length(); i += 2) {
		buff = hex.substr(i, 2);	
		try {
			char asciiChar = (char)std::stoi(buff, nullptr, 16);
			output.push_back(asciiChar);
		}
		catch (...) {
			throw std::invalid_argument("Invalid hex");
		}
	}
	return output;
}


std::vector<unsigned char> hexToBytes(std::string hex, int returnByteCount) {
    if (hex.length() / 2> returnByteCount) throw std::invalid_argument("Hex value too large");
    if (hex.length() % 2 != 0) throw std::invalid_argument("Missing hex digit");

    std::vector<unsigned char> output;
    output.reserve(hex.length() / 2);
	std::string buff;

    for (size_t i = 0; i < hex.length(); i += 2) {
        buff = hex.substr(i, 2);
		try {
			unsigned char byte = (unsigned char)(std::stoi(buff, nullptr, 16));
			output.push_back(byte);
		}
		catch (...) {
			throw std::invalid_argument("Invalid hex");
		}
    }

	int padLen = returnByteCount - output.size();
	if(padLen > 0) {
		output.insert(output.begin(), padLen, 0); // Prepend zeros
	}

    return output;
}

std::vector<unsigned char> getRandomIV(int byteCount) {
    std::vector<unsigned char> iv(byteCount);
    std::random_device rd; // Generate seed
    std::mt19937 gen(rd()); // Random number generator
    std::uniform_int_distribution<unsigned char> dis(0, 255); // Byte range [0, 255]

    for (int i = 0; i < byteCount; i++) {
        iv[i] = dis(gen);
    }

    return iv;
}
std::string bytesToHex(const std::vector<unsigned char>& bytes) {
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');

    for (unsigned char byte : bytes) {
        oss << std::setw(2) << static_cast<int>(byte);
    }

    return oss.str();
}

}
