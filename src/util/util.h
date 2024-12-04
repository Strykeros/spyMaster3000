#include <string>
#include <vector>

namespace util {

std::string strToHex(std::string str);
std::string hexToASCII(std::string hex);
std::vector<unsigned char> hexToBytes(std::string hex, int returnByteCount);
std::string bytesToHex(const std::vector<unsigned char>& bytes);
std::vector<unsigned char> getRandomIV(int byteCount);

}
