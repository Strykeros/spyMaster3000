#include "args.h"
#include <cstring>
#include "../spyMaster.h"
namespace Args {

std::vector<std::string> validAlgos = {DES, CAESER};

std::string selectedAlgo;
std::string plaintext;
util::word key;
int intKey;


bool isValidAlgo(std::string algo) {
	for(auto valid : validAlgos)
		if(algo == valid) return true;
	return false;
}
void parse(int argc, char* argv[]) {
	if(argc != 4) throw "Invalid argument count:\nRequired: <algorithm> <plain text> <key>";

	if(!isValidAlgo(argv[1])) throw "Invalid <algorithm> argument";
	selectedAlgo = argv[1];
	plaintext = argv[2];

	std::string argKey = argv[3];

	if(selectedAlgo.compare(CAESER) == 0) {
		try {intKey = std::stoi(argKey);}
		catch(...) {throw "Ceazer key must be a integer!";}
	} else if(selectedAlgo == DES) {

	}
}
}
