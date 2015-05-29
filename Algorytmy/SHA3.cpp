#include "SHA3.h"
#include "keccak.h"

SHA3::SHA3(const std::string& str){
	sha.resize(64, 0);
	keccak(reinterpret_cast<const uint8_t*>(str.c_str()), static_cast<int>(str.size()), sha.data(), 64);
}

SHA3::SHA3(FILE* fp){
	sha.resize(64, 0);
	if (fp!=nullptr)
		keccak(fp, sha.data(), 64);
}

const std::vector<unsigned char > & SHA3::pobierzKontener() const{
	return sha;
}


void SHA3::ascii2hex(unsigned char c, std::string & str) const{
	char pierwszy = (c >> 4) & 0x0F, drugi = c & 0x0F;
	if (pierwszy < 10){
		pierwszy += 0x30;
	} else{
		pierwszy += 55;
	}

	if (drugi < 10){
		drugi += 0x30;
	} else{
		drugi += 55;
	}
	str.push_back(pierwszy);
	str.push_back(drugi);
}