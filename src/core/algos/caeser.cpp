#include "caeser.h"
#include <iostream>

std::string caeser(std::string input, int key) {
	key = key % 26;

	std::string output;
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
namespace Caeser {

std::string encrypt(std::string input, std::string key) {
	int keyInt = std::stoi(key);
	std::cout << "enc " << key << std::endl;
	return caeser(input, keyInt);
}

std::string decrypt(std::string input, std::string key) {
	int keyInt = std::stoi(key);
	std::cout << "dec " << key << std::endl;
	return caeser(input, -keyInt);
}
}
