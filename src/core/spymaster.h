#pragma once

#include <map>
#include <string>
#include "algos/aes.h"

constexpr int INFINITE_LEN = -1;

typedef std::string(*EncryptFunc)(std::string, std::string);
typedef	std::string(*DecryptFunc)(std::string, std::string);

enum class Algo { AES128, AES192, AES256, DES, TDES_2KEY, TDES_3KEY, PLAYFAIR, CAESER };

struct AlgoSpec {
	const char* name;
	const int keyBitSize;
	const int blockBitSize;
	const EncryptFunc encrypt_ptr;
	const DecryptFunc decrypt_ptr;
	AlgoSpec(const char* n, int k, int b, EncryptFunc ec, DecryptFunc dc): 
		name(n), keyBitSize(k), blockBitSize(b), encrypt_ptr(ec), decrypt_ptr(dc) {};
};

const std::map<Algo, AlgoSpec> algoSpecs = {
	{Algo::AES128, AlgoSpec("AES128", 128, 128, aes::encrypt, aes::decrypt)},
	{Algo::AES192, AlgoSpec("AES192", 192, 128, nullptr, nullptr)},
	{Algo::AES256, AlgoSpec("AES256", 256, 128, nullptr, nullptr)},
	{Algo::DES, AlgoSpec("AES256", 64, 64, nullptr, nullptr)},
	{Algo::TDES_2KEY, AlgoSpec("Triple DES 2Key",128, 64, nullptr, nullptr)},
	{Algo::TDES_3KEY, AlgoSpec("Triple DES 2Key", 192, 64, nullptr, nullptr)},
	{Algo::PLAYFAIR, AlgoSpec("Playfair", 26, INFINITE_LEN, nullptr, nullptr)},
	{Algo::CAESER, AlgoSpec("Caeser", INFINITE_LEN, INFINITE_LEN, nullptr, nullptr)},
};






