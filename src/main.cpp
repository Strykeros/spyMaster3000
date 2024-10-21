#include "algos/des.h"
#include <iostream>
#include <ostream>
#include "util/args.h"
#include "algos/caeser.h"
#include "spyMaster.h"
#include "playfair.h"

void encrypt() {
	std::string encrypted;

	if(Args::selectedAlgo == CAESER) {
		encrypted = Caeser::encrypt(Args::text, Args::key_int);
	}
	else if (Args::selectedAlgo == PLAYFAIR) {
		encrypted = playfair::encrypt(Args::text, Args::key_str);
	}

	std::cout << encrypted << std::endl;
}

void decrypt() {
	std::string decrypted;

	if(Args::selectedAlgo == CAESER) {
		decrypted = Caeser::decrypt(Args::text, Args::key_int);
	}
	else if (Args::selectedAlgo == PLAYFAIR) {
		decrypted = playfair::decrypt(Args::text, Args::key_str);
	}

	std::cout << decrypted << std::endl;
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

