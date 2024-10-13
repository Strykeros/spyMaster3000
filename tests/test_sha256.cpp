#include "../external/googletest/googletest/include/gtest/gtest.h"
#include "../src/algos/sha256.cpp"
#include <cstring>
#include <string>

using namespace sha256;

TEST(SHA256PadTest, ShortMessage) {
    std::string msg = "abc";
	uint8_t expected[] = {'a', 'b', 'c', 0x80};
    padMsg(msg);

	EXPECT_EQ(blockCount, 1) << "Block count is not 1";
	EXPECT_TRUE(memcmp(M, expected, 4) == 0) << "First 4 bytes do not match";
	EXPECT_EQ(M[0][15], 0x18000000) << "Last byte is not length 24";
}

TEST(SHA256PadTest, LongMessage) {
	std::string msg = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
	padMsg(msg);

	EXPECT_EQ(blockCount, 2) << "Block count is not 2";
	EXPECT_TRUE(memcmp(M, msg.c_str(), msg.length()) == 0) << "Msg bytes do not match";
}
