#pragma once
#include <string>
#include "LoggerSymbol.h"

namespace SLog
{
	/**
	* Pobieranie nazwy klasy w stringu.
	* \author Daniel Wojdak
	* \version 1
	* \date 18-06-2014
	*/
#define NAZWAKLASY(C) SLog::LoggerNazwaKlasy::napis<C>()
#define NAZWAPOLA(C) #C

	/**
	* Klasa bazowa u¿ywana do stworzenia jednolitego interfajsu
	* dla klasy generuj¹cej logi z aplikacji.
	* \author Daniel Wojdak
	* \version 1
	* \date 18-06-2014
	*/
	class LOGGER_API LoggerNazwaKlasy {
	public:
		/**
		* Funkjca pobieraj¹ca nazwê klasy przekazanej jako argument szablonu.
		* \return Nazwa klasy przekazanej przez parametr szablonu.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-06-2014
		*/
		template< class C >
		static std::string napis() {
			return std::move(std::string(typeid(C).name()).substr(6));
		}
	};
}
