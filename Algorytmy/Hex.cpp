#include "Hex.h"

void Hex::dodaj(const std::string& s){
	for (auto c : s){
		dodaj(c);
	}
}

void Hex::dodaj(char c){
	char pierwszy = (c >> 4) & 0x0F;
	char drugi = c & 0x0F;
	
	pierwszy += (pierwszy < 10) ? 0x30 : 55;
	drugi += (drugi < 10) ? 0x30 : 55;

	napis_ += pierwszy;
	napis_ += drugi;
}

void Hex::dodaj(const std::vector < unsigned char >& v){
	for (auto c : v){
		dodaj((char)c);
	}
}

void Hex::dodaj(const char* c, unsigned int n){
	for (unsigned int i = 0; i < n; ++i){
		dodaj(c[i]);
	}
}

std::string Hex::pobierz() const{
	return napis_;
}
