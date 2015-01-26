#pragma once
#include <string>
#include <vector>
#include "keccak.h"

class SHA3
{
public:
	SHA3(const std::string& str);

	~SHA3() = default;

	void ascii2hex(unsigned char c, std::string & str);

	std::string pobierzNapis();

	const std::vector<unsigned char > & pobierzKontener();

private:
	std::vector<unsigned char> sha;
};

