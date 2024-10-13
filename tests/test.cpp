#include "../external/googletest/googletest/include/gtest/gtest.h"
#include "../src/algos/caeser.cpp"
#include <string>

TEST(Caeser, basic_test) {
	std::string plaintext = "My very big secret";
	std::string encrypted_expected = "Yk hqdk nus eqodqf";
	std::string encrypted = Caeser::encrypt(plaintext, 12);
	std::string decrypted = Caeser::decrypt(encrypted, 12);

	EXPECT_EQ(encrypted, encrypted_expected);
	EXPECT_EQ(decrypted, plaintext);
}

TEST(Caeser, key_zero) {
	std::string plaintext = "This plaintext is encrypted with key zero";
	std::string encrypted_expected =  plaintext;
	std::string encrypted = Caeser::encrypt(plaintext, 15);
	std::string decrypted = Caeser::decrypt(encrypted, 15);

	EXPECT_EQ(encrypted, encrypted_expected);
	EXPECT_EQ(decrypted, plaintext);
}

