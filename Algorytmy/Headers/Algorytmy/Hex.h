#pragma once
#include "AlgorytmySymbol.h"
#include <string>

class ALGORYTMY_API Hex
{
public:
	Hex() = default;
	void dodaj(const std::string&);
	void dodaj(char);
	void dodaj(const char*, unsigned int);
	std::string pobierz() const;
	~Hex() = default;
private:
	std::string napis_;
};
