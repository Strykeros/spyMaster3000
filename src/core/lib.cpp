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
namespace spymaster {
	std::string encryptFile(AlgoArgs& args);	

	std::string decryptFile(AlgoArgs& args);	

	std::string encryptText(AlgoArgs& args) {
		for(auto b : args.IV) {
			std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)b;
		}
		std::cout << std::endl;
		return ECB_Cryption(args, true);
	}	

	std::string decryptText(AlgoArgs& args) {
		return ECB_Cryption(args, false);
	}
}
