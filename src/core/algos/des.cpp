#include "des-tables.h"
#include <cassert>
#include <cstdint>
#include <cstring>
#include <string>
#include "des.h"

namespace des {
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

word des(word text, word key, bool encrypt) {
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

word tripleDes(word text, word key1, word key2, bool encrypt) {
	word step1 = des(text, key1, encrypt);
	word step2 = des(step1, key2, !encrypt);
	word step3 = des(step2, key1, encrypt);

	return step3;
}

std::string encrypt(std::string input, std::string key) {
	assert(input.length() == 8);
	assert(key.length() == 8);

	word inputWord;
	std::memcpy(&inputWord, input.data(), 8);

	word keyWord;
	std::memcpy(&keyWord, input.data(), 8);

	word output = des(inputWord, keyWord, true);

	std::string outputStr(reinterpret_cast<char*>(&output), 8);
	return outputStr;
	//return std::to_string(output);
}

std::string decrypt(std::string input, std::string key) {
	assert(input.length() == 8);
	assert(key.length() == 8);

	//word inputWord = (word)input.data();
	//word keyWord = (word)key.data();
	word inputWord;
	std::memcpy(&inputWord, input.data(), 8);

	word keyWord;
	std::memcpy(&keyWord, input.data(), 8);

	word output = des(inputWord, keyWord, false);

	std::string outputStr(reinterpret_cast<char*>(&output), 8);
	return outputStr;
	//return std::to_string(output);
}

}
