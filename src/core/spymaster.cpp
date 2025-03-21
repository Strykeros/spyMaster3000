#include "spymaster.h"
#include <map>
#include "algos/aes.h"
#include "algos/des.h"
#include "algos/playfair.h"
#include "algos/caeser.h"

const std::map<Algo, AlgoSpec> algoSpecs = {
	{Algo::AES128, AlgoSpec("AES128", 128, 128, aes::encrypt, aes::decrypt)},
	{Algo::AES192, AlgoSpec("AES192", 192, 128, nullptr, nullptr)},
	{Algo::AES256, AlgoSpec("AES256", 256, 128, nullptr, nullptr)},
	{Algo::DES, AlgoSpec("DES", 64, 64, des::encrypt, des::decrypt)},
	{Algo::TDES_2KEY, AlgoSpec("Triple DES 2Key",128, 64, tdes_2key::encrypt, tdes_2key::decrypt)},
	{Algo::TDES_3KEY, AlgoSpec("Triple DES 2Key", 192, 64, tdes_3key::encrypt, tdes_3key::decrypt)},
	{Algo::PLAYFAIR, AlgoSpec("Playfair", 26*8, INFINITE_LEN, playfair::encrypt, playfair::decrypt)},
	{Algo::CAESER, AlgoSpec("Caeser", INFINITE_LEN, INFINITE_LEN, Caeser::encrypt, Caeser::decrypt)},
};

const AlgoSpec* getAlgoSpec(Algo algo) {
	return &algoSpecs.at(algo); 
}
