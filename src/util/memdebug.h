#include <iostream>
#include <string>
#include <bitset>
#include <iomanip>
#include <sstream>

namespace memdebug{

enum Base { HEX, BIT };
std::string byteAs(unsigned char b, Base base);

template <typename T>
void print(T value, const char* msg = nullptr, bool reverseEndian =false, Base base = HEX) {
	std::string output;

	if(msg) {
		output += msg;
		output += ": ";
	}
	
	unsigned char* ptr = (unsigned char*)&value;
	if(reverseEndian) {
		for(int i = sizeof(T)-1; i >= 0; i--) {
			output += byteAs(ptr[i], base) += " ";
		}
	} else {
		for(int i = 0; i < sizeof(T); i++) {
			output += byteAs(ptr[i], base) += " ";
		}
	}	

	std::cout << output << std::endl;
}
template <typename T>
void printArray(const T* arr, int size, const char* msg = nullptr, bool reverseEndian = false, Base base = HEX) {
	if(msg) {
		std::cout << "[" << msg << "]" << std::endl;
	}

	for(int i = 0; i < size; i++) {
		print(arr[i], nullptr, reverseEndian, base);
	}
}
}

