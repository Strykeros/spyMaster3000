#include "../external/googletest/googletest/include/gtest/gtest.h"
#include "../src/algos/sha256.cpp"
#include <cstdint>
#include <cstring>
#include <string>

using namespace sha256;

TEST(SHA256PadTest, ShortMessage) {
    std::string msg = "abc";
    padMsg(msg);

	ASSERT_EQ(N, 1) << "Block count is not 1";

	EXPECT_TRUE(memcmp(M, msg.c_str(), msg.length()) == 0) << "First 4 bytes do not match";

	msg.push_back(0x80); //byte signaling end of msg
	EXPECT_TRUE(memcmp(M, msg.c_str(), msg.length()) == 0) << "Next byte after msg is not 0x80";

	uint8_t* pLastByte = (uint8_t*)(M + N) - 1;
	uint8_t expected = 0b00011000; // 24
	EXPECT_EQ(*pLastByte,expected) << "Last byte is not msg length 24";
}

TEST(SHA256PadTest, LongMessage) {
	std::string msg = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
	padMsg(msg);

	ASSERT_EQ(N, 2) << "Block count is not 2";

	EXPECT_TRUE(memcmp(M, msg.c_str(), msg.length()) == 0) << "Msg bytes do not match";

	msg.push_back(0x80); //byte signaling end of msg
	EXPECT_TRUE(memcmp(M, msg.c_str(), msg.length()) == 0) << "Next byte after msg is not 0x80";

	uint16_t* pLast2Bytes = (uint16_t*)(M + N) - 1;
	uint16_t expected = 0b1100000000000001; // 56 in small endian notation
	EXPECT_EQ(*pLast2Bytes, expected) << "Last byte is not msg lenght 56";
}

/* TEST(MsgSchedule, LongMessage) {
    word* W = new word[16];
    word* expected =  new word[] {
	0x61626364, 0x696a6b6c,
	0x62636465, 0x6a6b6c6d,
	0x63646566, 0x6b6c6d6e,
	0x64656667, 0x6c6d6e6f,
	0x65666768, 0x6d6e6f70,
	0x66676869, 0x6e6f7071,
	0x6768696a, 0x80000000,
	0x68696a6b, 0x00000000,
    };

    padMsg("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq");
    prepareMsgSchedule(W, &M[0]);

    EXPECT_EQ(W, expected);	
    delete[] W;
    delete[] expected;
} */

TEST(SHA256Hash, ShortMessage) {
    digest result = hash("abc");
    digest expected = {0xba7816bf, 0x8f01cfea, 0x414140de, 0x5dae2223, 0xb00361a3, 0x96177a9c, 0xb410ff61, 0xf20015ad};
    EXPECT_EQ(result, expected);
}
