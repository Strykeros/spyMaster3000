#include "playfair.h"
#include <algorithm>
#include <cassert>
#include <regex>
#include <cstring>

namespace playfair {
// since the 5x5 cypher table contains 25 letters but
// the english alphabet has 26 letters, 1 letter must removed from the plain text
char removed_char = 'j';
char replacer_char = 'i';
// the plaintext cannot have conecutive same letters,
// so a bogus letter must be inserted
char bogus_char = 'x';


std::string createCypherTable(std::string key) {
	std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
	std::string table = key;
	for(char c : alphabet) {
		if(c == removed_char || key.find(c) != -1) continue;
		table.push_back(c);
	}

	return table;
}
std::string preprocessInput(std::string s) {
	// replace removed char
	std::replace(s.begin(), s.end(), removed_char, replacer_char);
    
    // insert bogus_char between identical characters
    static const std::regex re("(\\w)\\1");
    s = std::regex_replace(s, re, "$1x$1");

	// make sure s is even length
	if(s.length() % 2 != 0) {
		if(removed_char == 'a') s.push_back('b');
		else s.push_back('a');
	}

	return s;
}

std::string encrypt(std::string input, std::string key) {
	assert(key.length() <= 26);
	std::string ct = createCypherTable(key);
	input = preprocessInput(input);
	std::string output;

	for(int i = 0; i < input.length(); i+=2 ) {
		int i1 = ct.find(input.at(i));
		int i2 = ct.find(input.at(i+1));
		char o1, o2;

		// in the same column
		if(abs(i1-i2)%5 == 0) {
			o1 = i1+5<25 ? ct.at(i1+5) : ct.at(i1%5);	
			o2 = i2+5<25 ? ct.at(i2+5) : ct.at(i2%5);	
		}
		// in the same row
		else if(i1/5 == i2/5) {
			o1 = (i1+1)%5!=0 ? ct.at(i1+1) : ct.at(i1-4);
			o2 = (i2+1)%5!=0 ? ct.at(i2+1) : ct.at(i2-4);
		}
		// forms a square
		else {
			int offset = abs(i1%5-i2%5);	
			if(i1%5 > i2%5) offset *= -1;
			o1 = ct.at(i1+offset);
			o2 = ct.at(i2-offset);
		}

		output.push_back(o1);
		output.push_back(o2);
	}
	
	return output;
}
std::string decrypt(std::string input, std::string key) {
	assert(key.length() <= 26);

	std::string ct = createCypherTable(key);
	std::string output;

	for(int i = 0; i < input.length(); i+=2 ) {
		int i1 = ct.find(input.at(i));
		int i2 = ct.find(input.at(i+1));
		char o1, o2;

		// in the same column
		if(abs(i1-i2)%5 == 0) {
			o1 = i1-5>=0 ? ct.at(i1-5) : ct.at(i1+20);	
			o2 = i2-5>=0 ? ct.at(i2-5) : ct.at(i2+20);	
		}
		// in the same row
		else if(i1/5 == i2/5) {
			o1 = (i1)%5!=0 ? ct.at(i1-1) : ct.at(i1+4);
			o2 = (i2)%5!=0 ? ct.at(i2-1) : ct.at(i2+4);
		}
		// forms a square
		else {
			int offset = abs(i1%5-i2%5);	
			if(i1%5 > i2%5) offset *= -1;
			o1 = ct.at(i1+offset);
			o2 = ct.at(i2-offset);
		}

		output.push_back(o1);
		output.push_back(o2);
	}

	static const std::regex re("([a-zA-Z])x\\1");
	output = std::regex_replace(output, re, "$1$1");
	return output;
}
}
