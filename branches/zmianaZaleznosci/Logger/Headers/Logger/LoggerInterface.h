#pragma once
#include <string>
#include "ExportSymbol.h"
#include "LoggerNazwaKlasy.h"
/**
* Klasa bazowa u¿ywana do stworzenia jednolitego interfajsu
* dla klasy generuj¹cej logi z aplikacji.
*/
class LOGGER_API LoggerInterface {
public:
	/**
	* Funkcja s³u¿¹ca jako podstawa do tworzenia napisów z opisem klasy.
	* \return Napis zawieraj¹cy opis klasy.
	*/
	virtual std::string&& napis() const abstract;
};
