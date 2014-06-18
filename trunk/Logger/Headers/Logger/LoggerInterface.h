#pragma once
#include <string>
#include "LoggerSymbol.h"
#include "LoggerNazwaKlasy.h"

namespace SLog{
	/**
	* Klasa bazowa u�ywana do stworzenia jednolitego interfajsu
	* dla klasy generuj�cej logi z aplikacji.
	* \author Daniel Wojdak
	* \version 1
	* \date 18-06-2014
	*/
	class LOGGER_API LoggerInterface {
	public:
		/**
		* Funkcja s�u��ca jako podstawa do tworzenia napis�w z opisem klasy.
		* \return Napis zawieraj�cy opis klasy.
		* \author Daniel Wojdak
		* \version 1
		* \date 18-06-2014
		*/
		virtual std::string napis() const abstract;
	};
}
