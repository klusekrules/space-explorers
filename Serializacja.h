#pragma once
#include "parser\ticpp.h"

/**
* \brief Klasa abstrakcyjna dodaj�ca interfejs serializacji.
*
* Rozsze�a interfejs o zapis i odczyt danych z pliku xml.
*/
class Serializacja
{
public:
	
	/**
	* \brief Metoda zapisuj�ca.
	*
	* Metoda s�u��ca do zapisu danych do w�z�a xml podanego jako parametr.
	* \param[out] wezel - W�ze� do kt�rego s� zapisywane dane.
	* \return Zwracana jest warto�� true, je�eli zapisano obiekt poprawnie. False, je�eli zapis si� nie powi�d�.
	* \warning Je�eli zwr�cono warto�� false w�ze� przekazany jako parametr nie jest zmodyfokowany.
	*/
	virtual bool zapisz( TiXmlElement* wezel ) const = 0;

	/**
	* \brief Metoda odczytuj�ca.
	*
	* Metoda s�u��ca do odczytu danych z w�z�a xml podanego jako parametr.
	* \param[in] wezel - W�ze� z kt�rego s� odczytywane dane.
	* \return Zwracana jest warto�� true, je�eli odczytano obiekt poprawnie. False, je�eli odczyt si� nie powi�d�.
	* \warning Metoda nie modyfikuje w�z�a.
	* \warning Je�eli metoda zwr�ci warto�� false, obiekt mo�e znajdowa� si� w stanie nieustalonym. Nie jest zalecane u�ywanie takiego obiektu.
	*/
	virtual bool odczytaj( TiXmlElement* wezel ) = 0;
};
