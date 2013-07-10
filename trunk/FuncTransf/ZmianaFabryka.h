#pragma once
#include "ExportSymbol.h"
#include "..\parser\ticpp.h"
#include "ZmianaInterfejs.h"
#include <map>
#include <memory>
#include "..\Logger\Log.h"
using std::shared_ptr;
using std::map;

/**
* \brief Fabryka klas zmian
*
* Klasa tworz�ca instacje klas zmian. Klasa implementuje wzorzec singleton.
* \author Daniel Wojdak
* \version 1
* \date 10-07-2013
*/
class FUNCTRANSF_API ZmianaFabryka
{
public:
	/**
	* Prototyp funkcji tworz�cej instacj� obiektu danej klasy.
	* \param[in] wezel - Wezel na podstawie, kt�rego tworzony jest obiekt.
	* \return Wska�nik na obiekt pochodny po ZmianaInterfejs.
	*/
	typedef ZmianaInterfejs* (*KreatorZmiany)( TiXmlElement* wezel );

	/**
	* Prototyp funkcji rejestruj�cej klas� zmiany w fabryce.
	* \param[in,out] fabryka - Instacja fabryki, w kt�rej nale�y zarejestrowa� zmian�, aby aplikacja potrafi�a utworzy� obiekt zmiany.
	* \param[in,out] logger - Instacja loggera do wy�wietlania komunikat�w o b��dach.
	* \return Funkcja powinna zwraca� true, je�li rejestracja si� powiedzie lub false w przeciwnym wypadku.
	* \warning Funkcja powonna wywo�ywa� na rzecz obiektu fabryka metod� RejestracjaZmiany.
	* \sa RejestracjaZmiany()
	*/
	typedef bool (*RejestrujZmiane)( ZmianaFabryka& fabryka , Log& logger );

	/**
	* Metoda pobieraj�ca instancj� klasy ZmianaFabryka.
	* \return Obiekt klasy ZmianaFabryka.
	*/
	static ZmianaFabryka& pobierzInstancje();
	
	/**
	* Metoda tworz�ca obiekt klasy zmiana zarejestrownej w fabryce, na podstawie w�z�a przekazanego przez parametr wezel. Wywo�uje ona funckj� zarejestrowan� przez metod� rejestracjaZmiany i przekazuje jej wezel.
	* \param[in] wezel - W�ze� na podstawie, kt�rego tworzony jest obiekt klasy zmiana.
	* \return Metoda zwraca inteligenty wska�nik na utworzony obiekt. Je�eli operacja si� nie powiedzie zwracany jest wska�nik na nullptr.
	* \warning Metoda wymaga, aby w w�le by� atrybut o nazwie zdefiniowanej przez ATRYBUT_XML_IDENTYFIKATOR zawieraj�cy identyfikator podany podczas rejestracji w funkcji rejestracjaZmiany.
	* \sa rejestracjaZmiany(), ATRYBUT_XML_IDENTYFIKATOR
	*/
	shared_ptr<ZmianaInterfejs> Tworz( TiXmlElement* wezel ) const;

	/**
	* Metoda rejestruj�ca funkcj� tworz�c� obiekt pochodny po ZmianaInterfejs.
	* \param[in] identyfikator - Identyfikator funckji.
	* \param[in] funkcja - Funkcja tworz�ca.
	* \return Metoda zwraca true, je�eli rejestracja si� powiedzie lub false w przeciwnym wypadku.
	* \warning Zabronionym identyfikatorem jest 0. Je�eli poda si� taki identyfikator to metoda zawsze zwr�ci warto�� false. Jest to podyktowane implementaj� metody. Inne warunki kiedy metoda zwr�ci false to: funkcja wskazuje na nullptr lub identyfikator zosta� ju� u�yty.
	*/
	bool rejestracjaZmiany(int identyfikator, KreatorZmiany funkcja );

private:

	/**
	* Typ zbioru funkcji tworz�cych obiekt.
	*/
	typedef map<int, KreatorZmiany> Callbacks;
	Callbacks callbacks_; // S�ownik funkcji tworz�cych obiekty pochodzne po ZmianaInterfejs.

	/**
	* Konstruktor bezparametrowy.
	*/
	ZmianaFabryka();

	/**
	* Konstruktor kopiuj�cy.
	* \param[in] obiekt - Obiekt klasy ZmianaFabryka, z kt�rego zostanie utworzony kolejny obiekt.
	*/
	ZmianaFabryka( const ZmianaFabryka& obiekt );

	/**
	* Operator przypisania.
	* \param[in] obiekt - Obiekt klasy ZmianaFabryka, z kt�rego zostanie utworzona kopia.
	* \return Referencja do obiektu klasy ZmianaFabryka.
	*/
	ZmianaFabryka& operator=(const ZmianaFabryka& obiekt );
};
