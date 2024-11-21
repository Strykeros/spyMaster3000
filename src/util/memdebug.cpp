#include "memdebug.h"

namespace memdebug {
using Base = memdebug::Base;

std::string byteAs(unsigned char b, Base base) {
	switch(base) {
		case Base::BIT:
			return std::bitset<8>(b).to_string();
		case Base::HEX: {
			std::ostringstream oss;
			oss << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(b);
			return oss.str();
		}
		default:
			throw std::invalid_argument("Unsupported base");
	}
}
}


