#include "lib.h"
#include "spymaster.h"
#include <cstdint>
#include <iomanip>


// PKCS7 padding
void padInput(std::string& msg, int desiredBlockByteSize) {
	if(msg.length() % desiredBlockByteSize == 0) return;
	uint8_t padLen = desiredBlockByteSize - (msg.length() % desiredBlockByteSize);
	msg.append(padLen, (char)padLen);
}

void unpadOutput(std::string& msg, int desiredBlockByteSize) {
    uint8_t padLen = msg.back();

	if(padLen > desiredBlockByteSize) return;

    // Validate padding bytes
    for (int i = msg.length() - padLen; i < msg.length(); i++) {
        if (static_cast<uint8_t>(msg[i]) != padLen) {
			return;
        }
    }

    // Remove padding bytes
    msg.erase(msg.length() - padLen);
}

std::string ECB_Cryption(AlgoArgs& args, bool doEncryption) {
	const AlgoSpec* spec = getAlgoSpec(args.selectedAlgo);
	assert(spec->blockBitSize != INFINITE_LEN);
	int blockByteSize = spec->blockBitSize / 8;

	if(doEncryption) padInput(args.input, blockByteSize);

	int blockCount = args.input.length() / blockByteSize; 
	std::string output;
	
	for(int i = 0; i < args.input.length(); i += blockByteSize) {
		std::string chunk = args.input.substr(i, blockByteSize);
		if(doEncryption) {
			output += spec->encrypt_ptr(chunk, args.key);
		}
		else {
			output += spec->decrypt_ptr(chunk, args.key);
		}
	}

	if(!doEncryption) unpadOutput(output, blockByteSize);

	return output;
}

void xorBlock(std::string& target, std::string& other) {
	assert(target.length() == other.length());
	for(int i = 0; i < target.length(); i ++) {
		target[i] ^= other[i];
	}
}
std::string CBC_Cryption(AlgoArgs& args, bool doEncryption) {
	const AlgoSpec* spec = getAlgoSpec(args.selectedAlgo);
	assert(spec->blockBitSize != INFINITE_LEN);
	int blockByteSize = spec->blockBitSize / 8;

	if(doEncryption) padInput(args.input, blockByteSize);

	int blockCount = args.input.length() / blockByteSize; 
	std::string output;
	std::string prevBlock(args.IV.begin(), args.IV.end()); 
	
	for(int i = 0; i < args.input.length(); i += blockByteSize) {
		std::string chunk = args.input.substr(i, blockByteSize);
		std::string processedBlock;
		if(doEncryption) {
			xorBlock(chunk, prevBlock);
			processedBlock = spec->encrypt_ptr(chunk, args.key);
			prevBlock = processedBlock;
		}
		else {
			processedBlock = spec->decrypt_ptr(chunk, args.key);
			xorBlock(processedBlock, prevBlock);
			prevBlock = chunk;
		}

		output += processedBlock;
	}

	if(!doEncryption) unpadOutput(output, blockByteSize);

	return output;
}

std::string infiniteLenCryption(AlgoArgs& args, bool doEncryption) { 
	const AlgoSpec* spec = getAlgoSpec(args.selectedAlgo);
	assert(spec->blockBitSize == INFINITE_LEN);

	std::string output;
	
	if(doEncryption) {
		output = spec->encrypt_ptr(args.input, args.key);
	}
	else {
		output = spec->decrypt_ptr(args.input, args.key);
	}

	return output;
}
namespace spymaster {
	std::string encryptFile(AlgoArgs& args);	

	std::string decryptFile(AlgoArgs& args);	

	std::string encryptText(AlgoArgs& args) {
		const AlgoSpec* spec = getAlgoSpec(args.selectedAlgo);
		if(spec->blockBitSize == INFINITE_LEN) {
			return infiniteLenCryption(args, true);
		}
		switch (args.cipherMode) {
			case CipherMode::ECB:
				return ECB_Cryption(args, true);
			case CipherMode::CBC:
				return CBC_Cryption(args, true);
			defult:
				return "twinkle dingle";
		}
	}	

	std::string decryptText(AlgoArgs& args) {
		const AlgoSpec* spec = getAlgoSpec(args.selectedAlgo);
		if(spec->blockBitSize == INFINITE_LEN) {
			return infiniteLenCryption(args, false);
		}

		switch (args.cipherMode) {
			case CipherMode::ECB:
				return ECB_Cryption(args, false);
			case CipherMode::CBC:
				return CBC_Cryption(args, false);
			defult:
				return "twinkle dingle";
		}
	}
}
