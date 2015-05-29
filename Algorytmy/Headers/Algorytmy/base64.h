#pragma once
#include "AlgorytmySymbol.h"
#include <string>
#include <vector>

std::string ALGORYTMY_API base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);
std::string ALGORYTMY_API base64_encode(const std::string & dane);
std::string ALGORYTMY_API base64_decode(std::string const& encoded_string);


class ALGORYTMY_API Base64
{
public:
	Base64();
	void dodaj(const std::string&);
	void dodaj(char);
	void dodaj(const std::vector < unsigned char >&);
	void dodaj(const char*, unsigned int);
	std::string pobierz() const;
	~Base64() = default;
private:
	char tab_[3];
	char size_ = 0;
	std::string napis_;

	void dopisz();
};

