#pragma once

#include <cassert>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <string>

namespace aes {
union Block {
	uint8_t matrix[4][4];
	uint8_t bytes[16];
	uint32_t rows[4];
		
	uint32_t getCol(int c) {
		uint32_t col = 0;
		for(int r = 0; r < 4; r++)
			col |= this->matrix[r][c] << (8*r);
		return col;
	}

	std::string toString() {
		std::ostringstream oss;
		for (int i = 0; i < 16; ++i) {
			oss << std::hex << std::setw(2) << std::setfill('0') << (int)this->bytes[i];
		}
		return oss.str();
	}

	Block(std::string text) {
		assert(text.length() == 16);
		std::memcpy(this, text.data(), 16);
	}

	Block(uint8_t* bytes) {
		for (int c = 0; c < 4; c++) {
			for (int r = 0; r < 4; r++) {
				this->matrix[r][c] = bytes[4*c+r];	
			}
		}
	}

	Block() {}
};
std::string encrypt(std::string input, std::string key);
std::string decrypt(std::string input, std::string key);
}
