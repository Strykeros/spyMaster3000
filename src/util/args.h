#pragma once

#include <string>
#include <cstdlib>  

namespace Args {
	extern std::string selectedAlgo;
	extern std::string text;
	extern int key_int;
	extern std::string key_str;
	extern bool doDecrypt;
	void parse(int argc, char* argv[]);
}

