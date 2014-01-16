#pragma once
#include <string>
#include "LoggerSymbol.h"

namespace SLog
{
	/**
	* Pobieranie nazwy klasy w stringu.
	*/
#define NAZWAKLASY(C) LoggerNazwaKlasy::napis<C>()

	/**
	* Klasa bazowa u¿ywana do stworzenia jednolitego interfajsu
	* dla klasy generuj¹cej logi z aplikacji.
	*/
	class LOGGER_API LoggerNazwaKlasy {
	public:
		/**
		* Funkjca pobieraj¹ca nazwê klasy przekazanej jako argument szablonu.
		* \return Nazwa klasy przekazanej przez parametr szablonu.
		*/
		template< class C >
		static std::string&& napis() {
			return std::string(typeid(C).name()).substr(6);
		}
	};
}
