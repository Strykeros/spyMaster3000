#include "algos/des.h"
#include <fstream>
#include <iostream>
#include <ostream>
#include "util/args.h"
#include "algos/caeser.h"
#include "spyMaster.h"
#include "playfair.h"
#include "algos/aes.h"


void writeToFile(std::string text, std::string filePath) {
	std::ofstream file;
	file.open(filePath);

	if(!file.is_open()) {
		std::cout << "Error writing to file!\n";
		return;
	}

	file << text;
	file.close();
	std::cout << "Writen to '" << filePath << "'!\n"; 
}

std::string aesEncrypt(std::string input, const std::string key, bool decrypt = false) {
	const int chunkSize = 16;

	std::string output;

	if(input.length() != chunkSize) {
		int padLen = chunkSize - (input.length() % chunkSize);
		input.append(padLen, ' ');
	}

	for(int i = 0; i < input.length(); i += chunkSize) {
		std::string chunk = input.substr(i, chunkSize);
		if(decrypt) {
			output += aes::decrypt(chunk, key);
		}
		else {
			output += aes::encrypt(chunk, key);
		}
	}

	return output;

}
void encrypt() {
	std::string encrypted;

	if(Args::selectedAlgo == CAESER) {
		encrypted = Caeser::encrypt(Args::text, Args::key_int);
	}
	else if (Args::selectedAlgo == PLAYFAIR) {
		encrypted = playfair::encrypt(Args::text, Args::key_str);
	}
	else if (Args::selectedAlgo == AES) {
		encrypted = aesEncrypt(Args::text, Args::key_str); 
	}

	if(Args::outputToFile) {
		writeToFile(encrypted, Args::outputFilePath);	
	}
	else {
		std::cout << encrypted << std::endl;
	}
}

void decrypt() {
	std::string decrypted;

	if(Args::selectedAlgo == CAESER) {
		decrypted = Caeser::decrypt(Args::text, Args::key_int);
	}
	else if (Args::selectedAlgo == PLAYFAIR) {
		decrypted = playfair::decrypt(Args::text, Args::key_str);
	}
	else if(Args::selectedAlgo == AES) {
		decrypted = aesEncrypt(Args::text, Args::key_str, true);
	}

	if(Args::outputToFile) {
		writeToFile(decrypted, Args::outputFilePath);	
	}
	else {
		std::cout << decrypted << std::endl;
	}
}

int main(int argc, char* argv[]) {
	try {
		Args::parse(argc, argv);
	}	
	catch (const char* e) {
		std::cout << e << std::endl;
		return 1;
	}

	if(Args::doDecrypt) decrypt();
	else encrypt();

	return 0;
}

