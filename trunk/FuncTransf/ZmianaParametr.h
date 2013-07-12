#pragma once
#include "ExportSymbol.h"
#include "..\parser\ticpp.h"
#include "..\Logger\LoggerInterface.h"
/**
* \brief Klasa reprezentuj�ca parametr zmiany. 
*
* Zalecana do przechowywania parametru we w�asnych dopisanych danych. Posiada zaimplemetowany konstruktor tworz�cy obiekt na podstawie w�z�a xml.
* \author Daniel Wojdak
* \version 1
* \date 10-07-2013
*/
class FUNCTRANSF_API ZmianaParametr:
	virtual public LoggerInterface
{
private:
	int idObiektu_; /// Identyfikatro obiektu.
	long double wspolczynnikObiektu_; /// Wsp�czynnik przechowywany przez parametr.
public:
	/**
	* Konstruktor tworz�cy obiekt na podstawie w�z�a.
	* \param[in] wezel - W�ze� drzewa XML.
	* \pre W�ze� powinien posiada� poprawne atrybuty o nazwach zdefiniowanych przez ATRYBUT_XML_IDENTYFIKATOR oraz ATRYBUT_XML_WSPOLCZYNNIK.
	* \sa ATRYBUT_XML_IDENTYFIKATOR, ATRYBUT_XML_WSPOLCZYNNIK
	*/
	ZmianaParametr( TiXmlElement* wezel );

	/**
	* \brief Destruktor
	*/
	virtual ~ZmianaParametr(void);

	/**
	* Metoda zwracaj�ca identyfikator obiektu.
	* \return Identyfikator obiektu.
	*/
	int pobierzIdentyfikatorObiektu()const;

	/**
	* Metoda zwracaj�ca wsp�czynnik obiektu.
	* \return Wsp�czynnik obiektu.
	*/
	long double pobierzWspolczynnik()const;

	/**
	* Metoda tworz�ca napis zawieraj�cy opis obiektu.
	* \return Opis obiektu.
	*/
	string napis () const override;
};
