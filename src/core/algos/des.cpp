#include "des-tables.h"
#include "../util/utility.h"
#include <vector>
#include "des.h"

using namespace util;

namespace DES {
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

std::vector<word> encrypt(const char* plaintext, word key) {
	std::vector<word> plainChunks = stringToChunks(plaintext);
	std::vector<word> encryptedChunks;

	for(const auto& chunk: plainChunks) {
		encryptedChunks.push_back(des(chunk, key, true));
	}

	return encryptedChunks;
	 
}
std::string decrypt(std::vector<word> encryptedChunks, word key) {
	std::vector<word> decryptedChunks;

	for(const auto& chunk : encryptedChunks) {
		decryptedChunks.push_back(des(chunk, key, false));
	}

	return chunksToString(decryptedChunks);
}
}
