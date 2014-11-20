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
#define NAZWAKLASY(C) typeid(C).name()
#define NAZWAKLASY2(C) typeid(C).name()
#define NAZWAPOLA(C) #C

	/**
	* Klasa bazowa u¿ywana do stworzenia jednolitego interfajsu
	* dla klasy generuj¹cej logi z aplikacji.
	* \author Daniel Wojdak
	* \version 3
	* \date 20-11-2014
	*/
	class LOGGER_API LoggerNazwaKlasy {
	public:
		/**
		* Funkjca pobieraj¹ca nazwê klasy przekazanej jako argument szablonu.
		* \return Nazwa klasy przekazanej przez parametr szablonu.
		* \author Daniel Wojdak
		* \version 3
		* \date 20-11-2014
		*/
		template< class C >
		static std::string napis() {
			std::string name(typeid(C).name());
			return std::move(name);
		}

		/**
		* Funkjca pobieraj¹ca nazwê klasy przekazanej jako argument szablonu.
		* \param[in] e - element którego typ zostanie zwrócony.
		* \return Nazwa klasy przekazanej przez parametr szablonu.
		* \author Daniel Wojdak
		* \version 1
		* \date 20-11-2014
		*/
		template< class C >
		static std::string napis( const C & e ) {
			std::string name(typeid(e).name());
			return std::move(name);
		}
	};
}
