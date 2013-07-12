#pragma once
#include "ExportSymbol.h"
#include <string>
using std::string;

/**
* Pobieranie nazwy klasy w stringu.
*/
#define NAZWAKLASY(C) LoggerNazwaKlasy::napis<C>()

/**
* Klasa bazowa u�ywana do stworzenia jednolitego interfajsu
* dla klasy generuj�cej logi z aplikacji.
*/
class LOGGER_API LoggerNazwaKlasy {
public:	
	/**
	* Funkjca pobieraj�ca nazw� klasy przekazanej jako argument szablonu.
	* \return Nazwa klasy przekazanej przez parametr szablonu.
	*/
	template< class C >
	static string napis() {
		return string(typeid(C).name()).substr(6);
	}
};
