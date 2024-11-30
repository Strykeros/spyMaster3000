#include <cassert>
#include <iomanip>
#include <sstream>
#include "util.h"

namespace util {

std::string strToHex(std::string str) {
	std::ostringstream output;
	for (unsigned char c : str)
		output << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
	return output.str();
}

std::string hexToASCII(std::string hex) {
	assert(hex.length() % 2 == 0 && "No half bytes! (2 hex digits = 1 byte)");

	std::string output;
	std::string buff;
	for(int i = 0; i < hex.length(); i += 2) {
		buff = hex.substr(i, 2);	
		char asciiChar = (char)std::stoi(buff, nullptr, 16);
		output.push_back(asciiChar);
	}
	return output;
}

}
