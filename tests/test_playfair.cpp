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
