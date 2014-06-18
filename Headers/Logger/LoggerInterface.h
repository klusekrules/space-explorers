#pragma once
#include <string>
#include "LoggerSymbol.h"
#include "LoggerNazwaKlasy.h"

namespace SLog{
	/**
	* Klasa bazowa u¿ywana do stworzenia jednolitego interfajsu
	* dla klasy generuj¹cej logi z aplikacji.
	* \author Daniel Wojdak
	* \version 1
	* \date 18-06-2014
	*/
	class LOGGER_API LoggerInterface {
	public:
		/**
		* Funkcja s³u¿¹ca jako podstawa do tworzenia napisów z opisem klasy.
		* \return Napis zawieraj¹cy opis klasy.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-06-2014
		*/
		virtual std::string napis() const abstract;
	};
}
