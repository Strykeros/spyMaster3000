#include "../external/googletest/googletest/include/gtest/gtest.h"
#include "../src/algos/sha256.cpp"
#include <cstdint>
#include <cstring>
#include <string>

using namespace sha256;

TEST(SHA256PadTest, ShortMessage) {
    std::string msg = "abc";
    padMsg(msg);

	ASSERT_EQ(blockCount, 1) << "Block count is not 1";

	EXPECT_TRUE(memcmp(M, msg.c_str(), msg.length()) == 0) << "First 4 bytes do not match";

	msg.push_back(0x80); //byte signaling end of msg
	EXPECT_TRUE(memcmp(M, msg.c_str(), msg.length()) == 0) << "Next byte after msg is not 0x80";

	uint8_t* pLastByte = (uint8_t*)(M + blockCount) - 1;
	uint8_t expected = 0b00011000; // 24
	EXPECT_EQ(*pLastByte,expected) << "Last byte is not msg length 24";
}

TEST(SHA256PadTest, LongMessage) {
	std::string msg = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
	padMsg(msg);

	ASSERT_EQ(blockCount, 2) << "Block count is not 2";

	EXPECT_TRUE(memcmp(M, msg.c_str(), msg.length()) == 0) << "Msg bytes do not match";

	msg.push_back(0x80); //byte signaling end of msg
	EXPECT_TRUE(memcmp(M, msg.c_str(), msg.length()) == 0) << "Next byte after msg is not 0x80";

	uint16_t* pLast2Bytes = (uint16_t*)(M + blockCount) - 1;
	uint16_t expected = 0b1100000000000001; // 56 in small endian notation
	EXPECT_EQ(*pLast2Bytes, expected) << "Last byte is not msg lenght 56";
}
