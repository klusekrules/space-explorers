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
};
