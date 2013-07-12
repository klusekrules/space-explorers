#pragma once
#include "ExportSymbol.h"
#include "..\parser\ticpp.h"
#include "..\Logger\LoggerInterface.h"
/**
* \brief Klasa reprezentuj¹ca parametr zmiany. 
*
* Zalecana do przechowywania parametru we w³asnych dopisanych danych. Posiada zaimplemetowany konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
* \author Daniel Wojdak
* \version 1
* \date 10-07-2013
*/
class FUNCTRANSF_API ZmianaParametr:
	virtual public LoggerInterface
{
private:
	int idObiektu_; /// Identyfikatro obiektu.
	long double wspolczynnikObiektu_; /// Wspó³czynnik przechowywany przez parametr.
public:
	/**
	* Konstruktor tworz¹cy obiekt na podstawie wêz³a.
	* \param[in] wezel - Wêze³ drzewa XML.
	* \pre Wêze³ powinien posiadaæ poprawne atrybuty o nazwach zdefiniowanych przez ATRYBUT_XML_IDENTYFIKATOR oraz ATRYBUT_XML_WSPOLCZYNNIK.
	* \sa ATRYBUT_XML_IDENTYFIKATOR, ATRYBUT_XML_WSPOLCZYNNIK
	*/
	ZmianaParametr( TiXmlElement* wezel );

	/**
	* \brief Destruktor
	*/
	virtual ~ZmianaParametr(void);

	/**
	* Metoda zwracaj¹ca identyfikator obiektu.
	* \return Identyfikator obiektu.
	*/
	int pobierzIdentyfikatorObiektu()const;

	/**
	* Metoda zwracaj¹ca wspó³czynnik obiektu.
	* \return Wspó³czynnik obiektu.
	*/
	long double pobierzWspolczynnik()const;

	/**
	* Metoda tworz¹ca napis zawieraj¹cy opis obiektu.
	* \return Opis obiektu.
	*/
	string napis () const override;
};
