#include "caeser.h"

namespace Caeser {

	std::string encrypt(std::string input, int key) {
		std::string output;
		output.resize(input.length());

		for (char& c : input) {
			if(c >= 'A' && c <= 'Z')
				output.push_back((c - 'A' + key + 26) % 26 + 'A');
			else if(c >= 'a' && c <= 'z')
				output.push_back((c - 'a' + key + 26) % 26 + 'a');
			else
				output.push_back(c);
		}
		
		return output;
	}

	std::string decrypt(std::string input, int key) {
		return encrypt(input, -key);
	}
}
