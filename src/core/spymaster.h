#pragma once
#include <string>

constexpr int INFINITE_LEN = -1;

typedef std::string(*EncryptFunc)(std::string, std::string);
typedef	std::string(*DecryptFunc)(std::string, std::string);

enum class Algo { AES128, AES192, AES256, DES, TDES_2KEY, TDES_3KEY, PLAYFAIR, CAESER };
enum class CipherMode { NONE, ECB, CBC, CTR };

struct AlgoSpec {
	const char* name;
	const int keyBitSize;
	const int blockBitSize;
	const EncryptFunc encrypt_ptr;
	const DecryptFunc decrypt_ptr;
	AlgoSpec(const char* n, int k, int b, EncryptFunc ec, DecryptFunc dc): 
		name(n), keyBitSize(k), blockBitSize(b), encrypt_ptr(ec), decrypt_ptr(dc) {};
};

const AlgoSpec* getAlgoSpec(Algo algo);







