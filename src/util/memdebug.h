#include <iostream>
#include <stdexcept>
#include <string>
#include <bitset>
#include <iomanip>
#include <sstream>

template <typename T> class MemDebugger {
public:
	MemDebugger(std::string _base, bool _reverseEndian = false) {
		reverseEndian = _reverseEndian;
		if(_base != "hex" && _base != "bin")
			throw std::invalid_argument("Invalid Base. Should be 'hex' or 'bin'");
		base = _base;
	}

	void print(T value, const char* msg = nullptr) {
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

	void printArray(const T* arr, int size, const char* msg = nullptr) {
		if(msg) {
			std::cout << "[" << msg << "]" << std::endl;
		}

		for(int i = 0; i < size; i++) {
			print(arr[i]);
		}
	}

	void compare(T value1, T value2, 
				bool value1_reverseEndian = false, bool value2_reverseEndian = false) 
	{
		static const char* GREEN = "\033[32m";
		static const char* RED = "\033[31m";
		static const char* RESET = "\033[0m";

		std::string line1;
		std::string line2;

		unsigned char* ptr1 = (unsigned char*)&value1;
		unsigned char* ptr2 = (unsigned char*)&value2;

		int start_i = value1_reverseEndian ? sizeof(T) - 1 : 0;
		int end_i = value1_reverseEndian ? -1 : sizeof(T);
		int step_i = value1_reverseEndian ? -1 : 1;

		int start_j = value2_reverseEndian ? sizeof(T) - 1 : 0;
		int end_j = value2_reverseEndian ? -1 : sizeof(T);
		int step_j = value2_reverseEndian ? -1 : 1;

		for(int i = start_i, j = start_j; 
			i != end_i; 
			i += step_i, j += step_j) 
		{
			std::string b1 = byteAs(ptr1[i], base);
			std::string b2 = byteAs(ptr2[j], base);

			const char* color = ptr1[i] == ptr2[j] ? GREEN : RED;
			line1 += color + b1 + RESET + " ";
			line2 += color + b2 + RESET + " ";
		}

		std::cout << line1 << std::endl;
		std::cout << line2 << std::endl;
	}

	void compareArray(const T* value1, const T* value2, int size, 
				bool value1_reverseEndian = false, bool value2_reverseEndian = false) 
	{
		static const char* GREEN = "\033[32m";
		static const char* RED = "\033[31m";
		static const char* RESET = "\033[0m";

		std::string line1;
		std::string line2;


		int start_i = value1_reverseEndian ? sizeof(T) - 1 : 0;
		int end_i = value1_reverseEndian ? -1 : sizeof(T);
		int step_i = value1_reverseEndian ? -1 : 1;

		int start_j = value2_reverseEndian ? sizeof(T) - 1 : 0;
		int end_j = value2_reverseEndian ? -1 : sizeof(T);
		int step_j = value2_reverseEndian ? -1 : 1;

		for(int s = 0; s < size; s++) {
			unsigned char* ptr1 = (unsigned char*)&(value1[s]);
			unsigned char* ptr2 = (unsigned char*)&(value2[s]);
			for(int i = start_i, j = start_j; 
			i != end_i; 
			i += step_i, j += step_j) 
			{
				std::string b1 = byteAs(ptr1[i], base);
				std::string b2 = byteAs(ptr2[j], base);

				const char* color = ptr1[i] == ptr2[j] ? GREEN : RED;
				line1 += color + b1 + RESET + " ";
				line2 += color + b2 + RESET + " ";
			}
			line1 += "| ";
			line2 += "| ";
		}


		std::cout << line1 << std::endl;
		std::cout << line2 << std::endl;
	}
private:
	std::string byteAs(unsigned char b, std::string base) {
		if(base == "hex") {
			std::ostringstream oss;
			oss << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(b);
			return oss.str();
		}

		if(base == "bin") {
			return std::bitset<8>(b).to_string();
		}
		
		throw std::invalid_argument("Unsupported base");
	}
private:
	bool reverseEndian;
	std::string base;
};

