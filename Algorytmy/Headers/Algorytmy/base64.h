#pragma once
#include "AlgorytmySymbol.h"
#include <string>

std::string ALGORYTMY_API base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);
std::string ALGORYTMY_API base64_encode(const std::string & dane);
std::string ALGORYTMY_API base64_decode(std::string const& encoded_string);