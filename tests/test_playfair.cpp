#include <gtest/gtest.h>
#include "../src/algos/playfair.cpp"
using namespace playfair;

TEST(Playfair, preprocessInput) {
	EXPECT_EQ(preprocessInput("helloworld"), "helxloworlda");
}

TEST(Playfair, createCypherTable) {
	EXPECT_EQ(createCypherTable("computer"), "computerabdfghiklnqsvwxyz");
	EXPECT_EQ(createCypherTable("monarchy"), "monarchybdefgiklpqstuvwxz");
	EXPECT_EQ(createCypherTable("playfir"), "playfirbcdeghkmnoqstuvwxz");
}

TEST(Encrypt, hello_world) {
	std::string
		plainText = "helloworld",
		key = "playfir",
		expected = "kgyvrvvqgrbf";

	EXPECT_EQ(encrypt(plainText, key), expected);
}

TEST(Encrypt, computer) {
	std::string
		plainText = "communicate",
		key = "computer",
		expected = "omrmpcsgpter";

	EXPECT_EQ(encrypt(plainText, key), expected);
}

TEST(Encrypt, instrumentsz) {
	std::string
		plainText = "instrumentsz",
		key = "monarchy",
		expected = "gatlmzclrqtx";

	EXPECT_EQ(encrypt(plainText, key), expected);
}

TEST(Decrypt, hello_world) {
	std::string
		encrypted = "kgyvrvvqgrbf",
		key = "playfir",
		expected = "helloworlda";

	EXPECT_EQ(decrypt(encrypted, key), expected);
}

TEST(Decrypt, computer) {
	std::string
		encrypted = "omrmpcsgpter",
		key = "computer",
		expected = "communicate";

	EXPECT_EQ(decrypt(encrypted, key), expected);
}

TEST(Decrypt, instrumentsz) {
	std::string
		encrypted = "gatlmzclrqtx",
		key = "monarchy",
		expected = "instrumentsz";

	EXPECT_EQ(decrypt(encrypted, key), expected);
}
