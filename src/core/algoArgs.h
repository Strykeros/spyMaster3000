#include <cmath>
#include <stdexcept>
#include <string>
#include <map>
#include "spymaster.h"
#include "../util/util.h"

struct AlgoArgs {
	Algo selectedAlgo;
	std::string key;
	std::string input;
};

class AlgoArgsBuilder {
private:
	AlgoArgs args; // what is being built
	const AlgoSpec* spec; // the specicification to build against (used to validate build)
public:
	AlgoArgsBuilder(Algo _selectedAlgo) {
		args.selectedAlgo = _selectedAlgo; 
		spec = getAlgoSpec(_selectedAlgo);
	}

	void setKey(std::string _key) {
		int keyLen = _key.length();
		bool isInvalidKeySize;
		std::string errorMsg;

		if(args.selectedAlgo == Algo::PLAYFAIR) {
			isInvalidKeySize = keyLen < 0 || keyLen > 26;
			if(isInvalidKeySize) errorMsg = "Playfair key must be less than 26 characters";
		}	
		else {
			isInvalidKeySize = keyLen != spec->keyBitSize / 8 && spec->keyBitSize != INFINITE_LEN;
			if(isInvalidKeySize)
				errorMsg = std::string(spec->name) + " key lenght must equal " + std::to_string(spec->keyBitSize / 8) + " characters"; 
		}

		if(isInvalidKeySize) {
			throw errorMsg;
		}

		args.key = _key;
	}

	void setInputFromASCII(std::string _input) {
		args.input = _input;
	}

	void setInputFromHex(std::string _input) {
		try {
			args.input = util::hexToASCII(_input);
		} 
		catch (...) {
			throw std::string("Invalid hex value");	
		}
	}

	int getKeyRequiredBitSize() {
		return spec->keyBitSize;
	}

	void reset(Algo algo) {
		args.selectedAlgo = algo;	
		args.input.clear();
		args.key.clear();
		spec = getAlgoSpec(algo);
	}

	AlgoArgs build() {
		if(args.key.empty()) throw std::string("Key is not given");
		if(args.input.empty()) throw std::string("Input is not given");
		return args;
	}
};
