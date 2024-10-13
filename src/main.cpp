#include "algos/des.h"
#include <iostream>
#include <ostream>
#include "util/args.h"
#include "algos/caeser.h"
#include "spyMaster.h"

int main(int argc, char* argv[]) {
	try {
		Args::parse(argc, argv);
	}	
	catch (const char* e) {
		std::cout << e << std::endl;
		return 1;
	}

	std::string encrypted;
	std::string decrypted;

	if(Args::selectedAlgo == CAESER) {
		encrypted = Caeser::encrypt(Args::plaintext, Args::intKey);
		decrypted = Caeser::decrypt(encrypted, Args::intKey);
	}
	else if (Args::selectedAlgo == DES) {

	}
	
	std::cout << "PlainText: " << Args::plaintext << std::endl;
	std::cout << "Encrypted: " << encrypted << std::endl;
	std::cout << "Decrypted: " << decrypted << std::endl;

	return 0;
}
