#include <array>
#include <string>

namespace sha256 {
	typedef std::array<uint32_t, 8> digest; 
	digest hash(std::string msg);
}
