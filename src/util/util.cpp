#include <cassert>
#include <iomanip>
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
		char asciiChar = (char)std::stoi(buff, nullptr, 16);
		output.push_back(asciiChar);
	}
	return output;
}

}
