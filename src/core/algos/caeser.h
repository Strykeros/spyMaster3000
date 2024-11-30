#pragma once

#include <cstring>
#include <iostream>

namespace Caeser {
	std::string encrypt(std::string input, int key);
	std::string decrypt(std::string input, int key);	
}
