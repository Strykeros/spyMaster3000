#pragma once

#include "utility.h"
#include <cstdlib>  

namespace Args {
	extern std::string selectedAlgo;
	extern std::string plaintext;
	extern util::word key;
	extern int intKey;

	// return status code
	// 0 - success in parsing arguments
	// 1 - failure	
	void parse(int argc, char* argv[]);
}

