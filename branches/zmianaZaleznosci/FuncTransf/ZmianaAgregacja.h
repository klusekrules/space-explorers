#pragma once
#include "ExportSymbol.h"
#include <vector>
#include <memory>
#include "tinyxml2.h"
#include "..\Logger\LoggerInterface.h"
#include "ZmianaFabryka.h"

/**
* \brief Klasa zmiany agreguj�cej. 
*
* Spos�b dzia�ania metod policzWartosc klasy zmiana agregacja:
*	- Je�eli nastepna_ jest r�wna nullptr klasa zwraca wartosc.
*	- Je�eli nastepna_ jest r�na od nullptr
*		-# Wywo�ywana jest metoda policzWartosc na rzecz obiektu nastepna_.
*		-# Wywo�ywane s� metody policzWartosc na rzecz obiekt�w listaZmian_ i jako parametr wartosc przekazywana jest liczba zwr�cona przez obiekt nastepny_.
*		-# Sumowane s� wszytkie warto�ci zwr�cone przez obiekty listaZmian_ i zwracane z funkcji.
* \author Daniel Wojdak
* \version 1
* \date 10-07-2013
*/
class FUNCTRANSF_API ZmianaAgregacja :
	public ZmianaInterfejs,
	virtual public LoggerInterface
{
private:
	static ZmianaFabryka* fabryka_; ///  Wska�nik na fabryk� zmian.
	static const int identyfikator_; /// Identyfikator klasy przekazywany do fabryki.

	/**
	* Metoda tworz�ca obiekt a podstawie w�z�a.
	* \param[in] wezel - W�ze� na podstawie kt�rego tworzony jest obiekt.
	* \return Wska�nika na obiekt utworzonej zmiany.
	*/
	static ZmianaInterfejs* TworzZmianaAgregacja( tinyxml2::XMLElement* wezel );

	std::shared_ptr < ZmianaInterfejs > nastepna_; /// Nast�pna zmiana
	std::vector<std::shared_ptr < ZmianaInterfejs > > listaZmian_; /// Lista zmian, kt�rych warto�ci b�d� zsumowane.

public:

	/**
	* Metoda rejestruj�ca klas� w fabryce.
	* \param[in] fabryka - Referencja do globalnej fabryki.
	* \return Metoda zwraca warto�� true, je�eli uda si� zarejestrowa� klas�. Je�eli wyst�pi� b��d zwr�cona jest warto�� false.
	* \sa ZmianaFabryka
	*/
	static bool RejestrujZmianaAgregacja( ZmianaFabryka &fabryka );

	/**
	* Metoda wyliczaj�ca warto��.
	* Spos�b dzia�ania metod policzWartosc klasy zmiana agregacja:
	*	- Je�eli nastepna_ jest r�wna nullptr klasa zwraca wartosc.
	*	- Je�eli nastepna_ jest r�na od nullptr
	*		-# Wywo�ywana jest metoda policzWartosc na rzecz obiektu nastepna_.
	*		-# Wywo�ywane s� metody policzWartosc na rzecz obiekt�w listaZmian_ i jako parametr wartosc przekazywana jest liczba zwr�cona przez obiekt nastepny_.
	*		-# Sumowane s� wszytkie warto�ci zwr�cone przez obiekty listaZmian_ i zwracane z funkcji.
	* \param[in] wartosc - podstawowa warto�� parametru, dla k�trego b�dzie wyliczana modyfikacja warto�ci.
	* \param[in] poziom - poziom obiektu, dla kt�rego b�dzie wyliczana modyfikacja warto�ci.
	* \param[in] identyfikatorPlanety - identyfikator planety, na kt�rej znajduje si� obiekt.
	* \return Przeliczona warto�� atryutu.
	*/
	long double policzWartosc(long double wartosc, int poziom, int identyfikatorPlanety)const override;

	/**
	* Konstruktor obiektu na podstawie w�z�a XML.
	* \param[in] wezel - Wezel drzewa xml.
	* \pre W�ze� musi zawiera� nast�puj�c� struktur�
	* \code {.xml}
	*	<Zmiana id="n">
	*		<Zmiana id="x" for="nastepny">
	*		  <Param id="0" wspolczynnik="3.0"/>
	*		</Zmiana>
	*		<Zmiana id="y" for="brat">
	*		  <Param id="0" wspolczynnik="5.0"/>
	*		</Zmiana>
	*	</Zmiana>
	* \endcode
	* gdzie element�w \<Zmiana id="y" for="brat"\> mo�e by� wiele.
	*/
	explicit ZmianaAgregacja( tinyxml2::XMLElement* wezel );

	/**
	* Konstruktor kopiujacy
	* \param[in] obiekt - Obiekt na podstawie, kt�rego b�dzie utworzona kopia.
	*/
	ZmianaAgregacja( const ZmianaAgregacja& obiekt );

	/**
	* Operator przypisania
	* \param[in] obiekt - Obiekt na podstawie, kt�rego b�dzie utworzona kopia.
	* \return Referencje do obiektu.
	*/
	ZmianaAgregacja& operator=( const ZmianaAgregacja& obiekt );

	/**
	* Metoda tworzy kopi� obiektu.
	* \return Wska�nik do kopii obiektu.
	* \warning Zwr�cony wska�nik musi zostac zwolniony operatorem delete. 
	*/
	ZmianaAgregacja* Kopia()const override;

	/**
	* Destruktor
	*/
	virtual ~ZmianaAgregacja();

	/**
	* Metoda tworz�ca napis zawieraj�cy opis obiektu.
	* \return Opis obiektu.
	*/
	std::string&& napis() const override;
};
