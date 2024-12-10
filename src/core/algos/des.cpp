#include "des-tables.h"
#include <cassert>
#include <cstdint>
#include <cstring>
#include <iostream>
#include "des.h"

typedef uint64_t word;
typedef char byte; 

word permutate(word input, int* table, int inputSize, int outputSize) {
    word output = 0;
    for(int i = 0; i < outputSize; i++) {
        int m = table[i] - 1;
        output |= ((input >> (inputSize - 1 - m)) & 1) << (outputSize - 1 - i);
    }
    return output;
}

word bitShiftKey(word key, int round) {
	word key1 = (key >> 28) & 0xFFFFFFF;
	word key2 = key & 0xFFFFFFF;
	
	int n = shiftTable[round];
	key1 = ((key1 << n) | (key1 >> (28-n))) & 0xFFFFFFF;
	key2 = ((key2 << n) | (key2 >> (28-n))) & 0xFFFFFFF;

	key = (key1 << 28) | key2;
	return key;
}

word sBoxSubstitution(word R) {
	word newR = 0;
	for(int i = 0; i < 8; i++) {
		byte b = (byte)(R >> (42 - i*6)) & 0x3F;
		int row = (b & 0x20) >> 4 | (b & 0x1); 
		int col = (b & 0x1E) >> 1; 
		newR |= ((word)sBoxes[i][row * 16 + col]) << (28 - i*4); 
	}

	return newR;
}

void f(word& R, word& L, word* keys, int round, bool encrypt) {
 	if(round == 0) return;

	word tempL = L;
	L = R;

	int roundIndex = encrypt ? (16 - round) : (round - 1);

	R = permutate(R, expansionTable, 32, 48); 
	R = R ^ keys[roundIndex];
	R = sBoxSubstitution(R);
	R = permutate(R, pBox, 32, 32);
	R = R ^ tempL;
	
	round--;
	f(R, L, keys, round, encrypt);
}

word cipher(word text, word key, bool encrypt) {
	// generate R and L of the plain text
	text = permutate(text, initialPermTable, 64, 64);
	word R = text & 0xFFFFFFFF;
	word L = text >> 32;
   
	// genereate keys
	word keys[16];
	key = permutate(key, keyPermTable, 64, 56);
	for (int i = 0; i < 16; i++) {
		key = bitShiftKey(key, i);
		keys[i] = permutate(key, compresionTable, 56, 48);
	}
   
	// Perform main DES algoritym
	f(R, L, keys, 16, encrypt);
    
	// Combine L an R to get the final result
	word result = ((word)R << 32) | L;
	result = permutate(result, finalPermTable, 64, 64);
	return result;
}

word toWord(const std::string& str) {
    word result = 0;
    std::memcpy(&result, str.data(), 8);
    return __builtin_bswap64(result);
}

std::string toString(word value) {
    word result = __builtin_bswap64(value);
    return std::string(reinterpret_cast<char*>(&result), 8);
}

std::string tripleDES(std::string _input, std::string _key, int keyCount, bool encrypt) {
	assert(keyCount == 2 || keyCount == 3);

	word input = toWord(_input);

	word key1 = toWord(_key.substr(0, 8));
	word key2 = toWord(_key.substr(8, 8));
	word key3 = keyCount == 2 ? key1 : toWord(_key.substr(16, 8));

	word step1, step2, step3;

	if(encrypt || keyCount == 2) {
		step1 = cipher(input, key1, encrypt);
		step2 = cipher(step1, key2, !encrypt);
		step3 = cipher(step2, key3, encrypt);
	}
	else {
		step1 = cipher(input, key3, false);
		step2 = cipher(step1, key2, true);
		step3 = cipher(step2, key1, false);
	}


	return toString(step3);
}

namespace des {
std::string encrypt(std::string input, std::string key) {
	assert(input.length() == 8);
	assert(key.length() == 8);

	word inputWord = toWord(input);
	word keyWord = toWord(key);
	word output = cipher(inputWord, keyWord, true);

	return toString(output);
}

std::string decrypt(std::string input, std::string key) {
	assert(input.length() == 8);
	assert(key.length() == 8);

	word inputWord = toWord(input);
	word keyWord = toWord(key);
	word output = cipher(inputWord, keyWord, false);

	return toString(output);
}
}

namespace tdes_2key {
std::string encrypt(std::string input, std::string key) {
	assert(input.length() == 8);
	assert(key.length() == 16);

	return tripleDES(input, key, 2, true);
}

std::string decrypt(std::string input, std::string key) {
	assert(input.length() == 8);
	assert(key.length() == 16);

	return tripleDES(input, key, 2, false);
}
}

namespace tdes_3key {
std::string encrypt(std::string input, std::string key) {
	assert(input.length() == 8);
	assert(key.length() == 24);

	return tripleDES(input, key, 3, true);
}

std::string decrypt(std::string input, std::string key) {
	assert(input.length() == 8);
	assert(key.length() == 24);

	return tripleDES(input, key, 3, false);
}
}
/* using namespace des;
#include "../../util/util.cpp"
int main() {
	word input = 0x0123456789ABCDEF;
	word key = 0x133457799BBCDFF1;
	word encrypted = des::des(input, key, true);
	std::cout << "Encrypted: " << std::hex << encrypted << std::endl;

	word decrypted = des::des(encrypted, key, false);
	std::cout << "Decrypted: " << std::hex << decrypted << std::endl;

	std::string inputStr = "0123abcd";
	std::string keyStr = "mysecret";
	std::string encryptedStr = des::encrypt(inputStr, keyStr);
	std::cout << "Encrypted: " << util::strToHex(encryptedStr) << std::endl;

	std::string decryptedStr = des::decrypt(encryptedStr, keyStr); 
	std::cout << "Decrypted: " << decryptedStr << std::endl;
} */
