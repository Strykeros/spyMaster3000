#include "../util/utility.h"
#include <vector>

namespace DES {
	std::vector<util::word> encrypt(const char* plaintext, util::word key);
	std::string decrypt(std::vector<util::word> encryptedChunks, util::word key);
}
