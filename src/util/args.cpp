#include "args.h"
#include <cstring>
#include <iostream>
#include <set>
#include <unistd.h>
#include "../spyMaster.h"
namespace Args {

// public variables
std::string selectedAlgo;
std::string text;
int key_int;
std::string key_str;
bool doDecrypt = false;
bool outputToFile = false;
std::string outputFilePath;

// private variables
const std::set<std::string> validAlgos = {DES, TRIPLE_DES, CAESER, PLAYFAIR, AES};

void parse(int argc, char* argv[]) {
	// get and set selectedAlgo
	char c = getopt(argc, argv, "a:");	
	if(c != 'a') throw "First argument '-a' must specify what algorithm to use!";
	if(validAlgos.count(optarg) == 0) throw "Unknown algorithm!";
	selectedAlgo = optarg;

	//check if there is piped input
	if (!isatty(fileno(stdin))) {
		// No ideas how this works
		text.assign(std::istreambuf_iterator<char>(std::cin), std::istreambuf_iterator<char>());
	}

	while((c = getopt(argc, argv, "a:t:k:F:D")) != -1) {
		switch(c) {
		case 't':
			text = optarg;
			break;
		case 'k':
			if(selectedAlgo == CAESER) {
				try {key_int = atoi(optarg);}
				catch(...) {throw "Caeser key must be an intenger!";}
			}
			else if(selectedAlgo == PLAYFAIR) {
				if(strlen(optarg) > 25) throw "Playfair key cannot be longer than 25 character!";
				key_str = optarg;
			}
			else if(selectedAlgo == AES) {
				if(strlen(optarg) > 16) throw "AES key cannot be longer than 16 characters!";
				key_str = optarg;
			}
			else {
				key_str = optarg;
			}
			break;
		case 'D':
			doDecrypt = true;
			break;
		case 'F':
			outputToFile = true;
			outputFilePath = std::string(optarg);
			break;
		}

	}

	if(text.empty()) throw "Text argument '-t' not given!";
}
}
