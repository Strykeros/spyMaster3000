#include "core/lib.h"
#include <iostream>

int main() {
	AlgoArgsBuilder builder(Algo::AES128);
	builder.setKey("superDuperSecret");
	builder.setInputAsPlainText("fuck me in the ass");
	AlgoArgs args = builder.build();

	std::string encrypted = spymaster::encryptText(args);

	AlgoArgsBuilder builder2(Algo::AES128);
	builder2.setKey("superDuperSecret");
	builder2.setInputAsPlainText(encrypted);
	AlgoArgs args2;
	try {
		args2 = builder2.build();
	} catch(const char* err) {
		std::cout << err << "\n";
		return -1;
	}

	std::string decrypted = spymaster::decryptText(args2);

	std::cout << encrypted << "\n";
	std::cout << decrypted << "\n";
}
