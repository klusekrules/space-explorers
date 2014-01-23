#pragma once
#include <string>
#include <algorithm>
#include "Zmiana\ZmianaInterfejs.h"

class Utils
{
public:
	static std::shared_ptr<SZmi::ZmianaInterfejs> TworzZmiane( XmlBO::ElementWezla );

	static void generujWyjatekBleduStruktury(const STyp::Tekst& plik, const STyp::Ilosc& linia, XmlBO::ElementWezla wezel);

	template<class Map, class Key>
	static bool zamianaKlucza ( Map &kontener, Key &before, Key &after ){
		if(kontener.find(after) != kontener.end())
			return false;
		auto iterator = kontener.find(before);
		if(iterator == kontener.end())
			return false;
		auto obiekt = iterator->second;
		kontener.erase(iterator);
		kontener.insert(make_pair(after,obiekt));
		return true;
	}

	static void ascii2hex(std::string& str, unsigned char c);
	static void sha3(std::string& str);
};
