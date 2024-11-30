#include <cmath>
#include <string>
#include <map>
#include "spymaster.h"

struct AlgoArgs {
	Algo selectedAlgo;
	std::string key;
	std::string input;
};

class AlgoArgsBuilder {
private:
	AlgoArgs args;
	AlgoSpec spec;
public:
	AlgoArgsBuilder(Algo _selectedAlgo): spec(algoSpecs.at(_selectedAlgo)) {
		args.selectedAlgo = _selectedAlgo; 
	}

	void setKey(std::string _key) {
		bool isInvalidKeySize = _key.length() != spec.keyBitSize / 8 && spec.keyBitSize != -1; // -1 means infinite
		if(isInvalidKeySize) {
			throw std::string(spec.name) + " key lenght must be " + std::to_string(spec.keyBitSize); 
		}

		args.key = _key;
	}

	void setInputAsPlainText(std::string _input) {
		args.input = _input;
	}

	AlgoArgs build() {
		if(args.key.empty()) throw std::string("Key is not given");
		if(args.input.empty()) throw std::string("Input is not given");
		return args;
	}
};
