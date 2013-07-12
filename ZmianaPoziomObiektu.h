#pragma once
#include "FuncTransf\ZmianaFabryka.h"
#include "FuncTransf\ZmianaParametr.h"
/**
* \brief Klasa reprezentuj�ca zmian� poziom obiektu.
*
* Spos�b dzia�ania metody wyliczajacej:
*	- Zwraca poziom obiektu o id podanym w parametrze. Obiekt sprawdzany jest na planecie o id podanej jako 3 parametr funkcji.
* \author Daniel Wojdak
* \version 1
* \date 11-07-2013
*/
class ZmianaPoziomObiektu:
	public ZmianaInterfejs,
	virtual public LoggerInterface
{
private:
	static const int identyfikator_; /// Identyfikator klasy przekazywany do fabryki.

	/**
	* Metoda tworz�ca obiekt a podstawie w�z�a.
	* \param[in] wezel - W�ze� na podstawie kt�rego tworzony jest obiekt.
	* \return Wska�nika na obiekt utworzonej zmiany.
	*/
	static ZmianaInterfejs* TworzZmianaPoziomObiektu( TiXmlElement* wezel );

	ZmianaParametr parametr_; /// Identyfikator obiektu.
public:

	/**
	* Metoda rejestruj�ca klas� w fabryce.
	* \param[in] fabryka - Referencja do globalnej fabryki.
	* \return Metoda zwraca warto�� true, je�eli uda si� zarejestrowa� klas�. Je�eli wyst�pi� b��d zwr�cona jest warto�� false.
	* \sa ZmianaFabryka
	*/
	static bool RejestrujZmianaPoziomObiektu( ZmianaFabryka &fabryka );

	/**
	* Metoda wyliczaj�ca warto��.
	* Spos�b dzia�ania metod policzWartosc klasy zmiana agregacja:
	*	- Zwraca poziom obiektu o id podanym w parametrze. Obiekt sprawdzany jest na planecie o id podanej jako 3 parametr funkcji.
	* \param[in] wartosc - podstawowa warto�� parametru, dla k�trego b�dzie wyliczana modyfikacja warto�ci.
	* \param[in] poziom - poziom obiektu, dla kt�rego b�dzie wyliczana modyfikacja warto�ci.
	* \param[in] identyfikatorPlanety - identyfikator planety, na kt�rej znajduje si� obiekt.
	* \return Przeliczona warto�� atryutu.
	*/
	long double policzWartosc(long double wartosc, int poziom, int identyfikatorPlanety) const override;

	/**
	* Metoda tworzy kopi� obiektu.
	* \return Wska�nik do kopii obiektu.
	* \warning Zwr�cony wska�nik musi zostac zwolniony operatorem delete. 
	*/
	ZmianaPoziomObiektu* Kopia()const override;

	/**
	* Konstruktor obiektu na podstawie w�z�a XML.
	* \param[in] wezel - Wezel drzewa xml.
	* \pre W�ze� musi zawiera� nast�puj�c� struktur�
	* \code {.xml}
	*	<Zmiana id="n">
	*		<Param id="0x3"/>
	*	</Zmiana>
	* \endcode
	*/
	explicit ZmianaPoziomObiektu( TiXmlElement * wezel );

	/**
	* Destruktor
	*/
	virtual ~ZmianaPoziomObiektu();

	/**
	* Metoda tworz�ca napis zawieraj�cy opis obiektu.
	* \return Opis obiektu.
	*/
	string napis () const override;

};

/**
* Funkcja eksportowana s�u��ca do rejestracji zmiany w fabryce.
* \param[in,out] fabryka - Referencja do fabryki, w kt�rej ma zosta� zarejestrowana klasa.
* \param[in] logger - referencja do loggera, dla komunikacji o b��dach.
* \return Funkcja zwraca true, je�eli uda si� zarejestrowa� klas� lub false w przeciwnym wypadku.
*/
bool RejestrujZmianaPoziomObiektu ( ZmianaFabryka& fabryka , Log& logger );
