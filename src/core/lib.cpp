#include "lib.h"
#include "spymaster.h"
#include <ios>
#include <iostream>

std::string performCryption(AlgoArgs args, bool doDecryption = false) {
	const AlgoSpec* spec = getAlgoSpec(args.selectedAlgo);

	int blockByteSize = spec->blockBitSize / 8;
	std::string& input = args.input; 

	std::string output;

	if(spec->blockBitSize == INFINITE_LEN) {
		
		if(doDecryption) {
			output += spec->decrypt_ptr(input, args.key);
		}
		else {
			output += spec->encrypt_ptr(input, args.key);
		}

		return output;
	}

	if(input.length() != blockByteSize) {
		int padLen = blockByteSize - (input.length() % blockByteSize);
		input.append(padLen, ' ');
	}

	for(int i = 0; i < input.length(); i += blockByteSize) {
		std::string chunk = input.substr(i, blockByteSize);
		if(doDecryption) {
			output += spec->decrypt_ptr(chunk, args.key);
		}
		else {
			output += spec->encrypt_ptr(chunk, args.key);
		}
	}

	return output;
}
namespace spymaster {
	std::string encryptFile(const AlgoArgs& args);	

	std::string decryptFile(const AlgoArgs& args);	

	std::string encryptText(const AlgoArgs& args) {
		for (auto b : args.IV) {
			std::cout << std::hex << (int)b;
		}
		std::cout << std::endl;
		return performCryption(args);
	}	

	std::string decryptText(const AlgoArgs& args) {
		return performCryption(args, true);
	}
}
