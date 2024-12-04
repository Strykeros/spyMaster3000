#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "spymaster.h"
#include "../util/util.h"

struct AlgoArgs {
	Algo selectedAlgo;
	CipherMode cipherMode = CipherMode::NONE;
	std::vector<unsigned char> IV; //initilization vector	
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
			args.key.clear();
			throw errorMsg;
		}

		args.key = _key;
	}

	void setCipherMode(CipherMode cipherMode) {
		args.cipherMode = cipherMode;
	}

	void setIV(std::string IVStr) {
		std::vector<unsigned char> temp;			
		try {
			temp = util::hexToBytes(IVStr, spec->blockBitSize / 8); 	
		}
		catch (std::invalid_argument err) {
			args.IV.clear();
			throw std::string(err.what());	
		}
		
		args.IV = temp;
	}

	std::string setRandomIV() {
		args.IV = util::getRandomIV(spec->blockBitSize / 8);
		return util::bytesToHex(args.IV);
	}

	void setInputFromASCII(std::string _input) {
		args.input = _input;
	}

	void setInputFromHex(std::string _input) {
		try {
			args.input = util::hexToASCII(_input);
		} 
		catch (...) {
			args.input.clear();
			throw std::string("Invalid hex value");	
		}
	}
	
	// get info about the algo the builder is trying to build args for
	int getKeyRequiredBitSize() {
		return spec->keyBitSize;
	}

	int getBlockBitSize() {
		return spec->blockBitSize;
	}

	void reset(Algo algo) {
		args.selectedAlgo = algo;	
		args.input.clear();
		args.key.clear();
		args.cipherMode = CipherMode::NONE;
		args.IV.clear();
		spec = getAlgoSpec(algo);
	}

	AlgoArgs build() {
		if(args.key.empty()) throw std::string("Key is not given");
		if(args.input.empty()) throw std::string("Input is not given");
		bool IVRequired = spec->blockBitSize != INFINITE_LEN && args.cipherMode != CipherMode::ECB;
		if(IVRequired && args.IV.empty()) throw std::string("IV not given");
		
		// you fucked up if this is wrong
		assert(args.cipherMode != CipherMode::NONE || args.IV.size() == spec->blockBitSize / 8);

		return args;
	}
};
