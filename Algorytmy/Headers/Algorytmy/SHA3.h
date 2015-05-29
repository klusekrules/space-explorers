#pragma once
#include "AlgorytmySymbol.h"
#include <string>
#include <vector>

class ALGORYTMY_API SHA3
{
public:
	SHA3(const std::string& str);
	SHA3(FILE* fp);

	~SHA3() = default;

	void ascii2hex(unsigned char c, std::string & str) const;

	template<class T>
	std::string pobierzNapis() const{
		T konwerter;
		konwerter.dodaj(sha);
		return std::move(konwerter.pobierz());
	}

	const std::vector<unsigned char > & pobierzKontener() const;

private:
	std::vector<unsigned char> sha;
};

