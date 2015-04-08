#pragma once
#include <string>
#include <vector>
#include "keccak.h"

class SHA3
{
public:
	SHA3(const std::string& str);
	SHA3(FILE* fp);

	~SHA3() = default;

	void ascii2hex(unsigned char c, std::string & str) const;

	std::string pobierzNapis() const;

	const std::vector<unsigned char > & pobierzKontener() const;

private:
	std::vector<unsigned char> sha;
};

