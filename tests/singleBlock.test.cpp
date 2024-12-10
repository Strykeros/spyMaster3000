#include <gtest/gtest.h>
#include "../src/core/algos/aes.cpp"
#include "../src/core/algos/des.cpp"
#include "../src/util/util.cpp"

using namespace aes;

TEST(SingleBlock, aes128_simple) {
	std::string input = "0123456789abcdef";
	std::string key = "superDuperSecret";
	std::string encrypted = aes::encrypt(input, key);

	std::string expected = util::hexToASCII("145659F4B6B9C671B75829AFE7E726E7");
	ASSERT_EQ(encrypted, expected);

	std::string decrypted = aes::decrypt(encrypted, key); 

	ASSERT_EQ(decrypted, input);
}

TEST(SingleBlock, aes128_complex) {
	std::string input = "$*0;']f0as.~+<*n";
	std::string key = "<>?'{}_+*#894|~f";
	std::string encrypted = aes::encrypt(input, key);

	std::string expected = util::hexToASCII("59B8A214C74628D321974415E173CC3A");
	ASSERT_EQ(encrypted, expected);

	std::string decrypted = aes::decrypt(encrypted, key); 

	ASSERT_EQ(decrypted, input);
}

TEST(SingleBlock, des) {
	std::string input = "0123abcd";
	std::string key = "mysecret";
	std::string encrypted = des::encrypt(input, key);

	std::string expected = util::hexToASCII("2169773ddd170f08");
	ASSERT_EQ(encrypted, expected);

	std::string decrypted = des::decrypt(encrypted, key); 

	ASSERT_EQ(decrypted, input);
}

TEST(SingleBlock, tdes_3key) {
	std::string input = "0123abcd";
	std::string key = "mySuperDuperMegaSecretKe";
	std::string encrypted = tdes_3key::encrypt(input, key);

	std::string expected = util::hexToASCII("4547b56557c40eb3");
	ASSERT_EQ(encrypted, expected);

	std::string decrypted = tdes_3key::decrypt(encrypted, key); 

	ASSERT_EQ(decrypted, input);
}
