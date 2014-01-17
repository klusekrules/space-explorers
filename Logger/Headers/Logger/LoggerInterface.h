#pragma once
#include <string>
#include "LoggerSymbol.h"
#include "LoggerNazwaKlasy.h"

namespace SLog{
	/**
	* Klasa bazowa u�ywana do stworzenia jednolitego interfajsu
	* dla klasy generuj�cej logi z aplikacji.
	*/
	class LOGGER_API LoggerInterface {
	public:
		/**
		* Funkcja s�u��ca jako podstawa do tworzenia napis�w z opisem klasy.
		* \return Napis zawieraj�cy opis klasy.
		*/
		virtual std::string napis() const abstract;
	};
}
