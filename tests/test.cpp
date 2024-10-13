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
	std::string encrypted = Caeser::encrypt(plaintext, 0);
	std::string decrypted = Caeser::decrypt(encrypted, 0);

	EXPECT_EQ(encrypted, encrypted_expected);
	EXPECT_EQ(decrypted, plaintext);
}

TEST(Caeser, key_alphabet_size_26) {
	std::string plaintext = "This plaintext is encrypted witk key 26";
	// result should be the same as plaintext because key 26 wraps each letter back to itself
	std::string encrypted_expected =  plaintext;
	std::string encrypted = Caeser::encrypt(plaintext, 26);
	std::string decrypted = Caeser::decrypt(encrypted, 26);

	EXPECT_EQ(encrypted, encrypted_expected);
	EXPECT_EQ(decrypted, plaintext);
}

TEST(Caeser, key_69) {
	std::string plaintext = "My very big secret";
	// the result should be the same as with key 17 beacuse 69mod26 = 17
	std::string encrypted_expected = "Dp mvip szx jvtivk";
	std::string encrypted = Caeser::encrypt(plaintext, 69);
	std::string decrypted = Caeser::decrypt(encrypted, 69);

	EXPECT_EQ(encrypted, encrypted_expected);
	EXPECT_EQ(decrypted, plaintext);
}

TEST(Caeser, plaintext_gibberish) {
	std::string plaintext = "My  very big  0743 secret &&^^ d2f";
	// only english letters should change, everything else should remain the same as plaintext
	std::string encrypted_expected = "Gs  pyls vca  0743 mywlyn &&^^ x2z";
	std::string encrypted = Caeser::encrypt(plaintext, 20);
	std::string decrypted = Caeser::decrypt(encrypted, 20);

	EXPECT_EQ(encrypted, encrypted_expected);
	EXPECT_EQ(decrypted, plaintext);
}
