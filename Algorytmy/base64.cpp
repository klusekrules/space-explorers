/*
base64.cpp and base64.h

Copyright (C) 2004-2008 René Nyffenegger

This source code is provided 'as-is', without any express or implied
warranty. In no event will the author be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this source code must not be misrepresented; you must not
claim that you wrote the original source code. If you use this source code
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original source code.

3. This notice may not be removed or altered from any source distribution.

René Nyffenegger rene.nyffenegger@adp-gmbh.ch

*/
#include "base64.h"

static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";


static inline bool is_base64(unsigned char c) {
	return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
	std::string ret;
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	while (in_len--) {
		char_array_3[i++] = *(bytes_to_encode++);
		if (i == 3) {
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (i = 0; (i <4); i++)
				ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
			ret += base64_chars[char_array_4[j]];

		while ((i++ < 3))
			ret += '=';

	}

	return std::move(ret);

}

std::string base64_encode(const std::string & dane){
	return std::move(base64_encode(reinterpret_cast<const unsigned char*>(dane.c_str()), dane.length()));
}

std::string base64_decode(std::string const& encoded_string) {
	int in_len = encoded_string.size();
	int i = 0;
	int j = 0;
	int in_ = 0;
	unsigned char char_array_4[4], char_array_3[3];
	std::string ret;

	while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
		char_array_4[i++] = encoded_string[in_]; in_++;
		if (i == 4) {
			for (i = 0; i <4; i++)
				char_array_4[i] = base64_chars.find(char_array_4[i]);

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
				ret += char_array_3[i];
			i = 0;
		}
	}

	if (i) {
		for (j = i; j <4; j++)
			char_array_4[j] = 0;

		for (j = 0; j <4; j++)
			char_array_4[j] = base64_chars.find(char_array_4[j]);

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
	}

	return std::move(ret);
}

Base64::Base64(){
	tab_[0] = 0;
	tab_[1] = 0;
	tab_[2] = 0;
}

void Base64::dodaj(const std::string& s){
	for (auto c : s){
		dodaj(c);
	}
}

void Base64::dodaj(char c){
	tab_[size_++] = c;
	if (size_ >= 3)
		dopisz();
}
void Base64::dodaj(const std::vector < unsigned char >& v){
	for (auto c : v){
		dodaj((char)c);
	}
}

void Base64::dodaj(const char* c, unsigned int n){
	for (unsigned int i = 0; i < n; ++i){
		dodaj(c[i]);
	}
}

std::string Base64::pobierz() const{
	std::string ret = napis_;
	unsigned char char_array_4[4];
	
	char_array_4[0] = (tab_[0] & 0xfc) >> 2;
	char_array_4[1] = ((tab_[0] & 0x03) << 4) + ((tab_[1] & 0xf0) >> 4);
	char_array_4[2] = ((tab_[1] & 0x0f) << 2) + ((tab_[2] & 0xc0) >> 6);
	char_array_4[3] = tab_[2] & 0x3f;

	for (int j = 0; (j < size_ + 1); j++)
		ret += base64_chars[char_array_4[j]];

	int i = size_;
	while ((i++ < 3))
		ret += '=';

	return std::move(ret);
}

void Base64::dopisz(){
	unsigned char char_array_4[4];
	char_array_4[0] = (tab_[0] & 0xfc) >> 2;
	char_array_4[1] = ((tab_[0] & 0x03) << 4) + ((tab_[1] & 0xf0) >> 4);
	char_array_4[2] = ((tab_[1] & 0x0f) << 2) + ((tab_[2] & 0xc0) >> 6);
	char_array_4[3] = tab_[2] & 0x3f;
	for (int i = 0; i<4; i++)
		napis_ += base64_chars[char_array_4[i]];
	size_ = 0;
	tab_[0] = 0;
	tab_[1] = 0;
	tab_[2] = 0;
}