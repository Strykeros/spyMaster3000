#include "lib.h"
#include "spymaster.h"

std::string performCryption(AlgoArgs args, bool doDecryption = false) {
	const AlgoSpec* spec = getAlgoSpec(args.selectedAlgo);

	int blockByteSize = spec->blockBitSize / 8;
	std::string& input = args.input; 

	std::string output;

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
	std::string encryptFile(AlgoArgs args);	

	std::string decryptFile(AlgoArgs args);	

	std::string encryptText(AlgoArgs args) {
		return performCryption(args);
	}	

	std::string decryptText(AlgoArgs args) {
		return performCryption(args, true);
	}
}
