#pragma once
#include <string>
#include <algorithm>
#include "FuncTransf\ZmianaInterfejs.h"
#include "parser\ticpp.h"
#include "Tekst.h"
#include "Ilosc.h"
using namespace std;

class Utils
{
public:
	static shared_ptr<ZmianaInterfejs> TworzZmiane( TiXmlElement* );

	static void generujWyjatekBleduStruktury(  const Tekst& plik, const Ilosc& linia, TiXmlElement* wezel );

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

	static void ascii2hex(string& str, unsigned char c);
	static void sha3(string& str);
};
