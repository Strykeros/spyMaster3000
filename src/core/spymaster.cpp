#include "spymaster.h"
#include <map>
#include "algos/aes.h"
#include "algos/des.h"
#include "algos/playfair.h"

const std::map<Algo, AlgoSpec> algoSpecs = {
	{Algo::AES128, AlgoSpec("AES128", 128, 128, aes::encrypt, aes::decrypt)},
	{Algo::AES192, AlgoSpec("AES192", 192, 128, nullptr, nullptr)},
	{Algo::AES256, AlgoSpec("AES256", 256, 128, nullptr, nullptr)},
	{Algo::DES, AlgoSpec("DES", 64, 64, des::encrypt, des::decrypt)},
	{Algo::TDES_2KEY, AlgoSpec("Triple DES 2Key",128, 64, nullptr, nullptr)},
	{Algo::TDES_3KEY, AlgoSpec("Triple DES 2Key", 192, 64, nullptr, nullptr)},
	{Algo::PLAYFAIR, AlgoSpec("Playfair", 26*8, INFINITE_LEN, playfair::encrypt, playfair::decrypt)},
	{Algo::CAESER, AlgoSpec("Caeser", INFINITE_LEN, INFINITE_LEN, nullptr, nullptr)},
};

const AlgoSpec* getAlgoSpec(Algo algo) {
	return &algoSpecs.at(algo); 
}
