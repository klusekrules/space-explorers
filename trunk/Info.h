#pragma once
#include "Bazowa.h"
#include "Tekst.h"
#include "Identyfikator.h"
#include "Wymagania.h"
#include "WyjatekParseraXML.h"

/**
* \brief Klasa bazowa obiektu opisuj�cego.
*
* Klasa bazowa dla obiektu opisuj�cego. Zawiera podstawowy opis obiektu. Zawiera wymagania obiektu. 
* \author Daniel Wojdak
* \version 1
* \date 22-07-2013
*/
class Info:
	public Bazowa,
	public Wymagania,
	virtual public LoggerInterface
{
public:

	/**
	* \brief Konstruktor.
	* 
	* Podstawowy konstruktor obiektu.
	* \param[in] nazwa - Nazwa obiektu.
	* \param[in] opis - Opis obiektu.
	* \param[in] identyfikator - Identyfikator obiektu.
	* \param[in] wymagania - Wymagania obiektu.
	*/
	Info( const Tekst& nazwa, const Tekst& opis, const Identyfikator& identyfikator, const Wymagania& wymagania ) throw();

	/**
	* Konstruktor tworz�cy obiekt na podstawie w�z�a xml.
	* \param[in] wezel - W�ze� na podstawie, kt�rego jest tworzony obiekt.
	*/
	explicit Info( TiXmlElement * wezel ) throw(WyjatekParseraXML);

	/**
	* \brief Destruktor.
	*/
	virtual ~Info();

	/**
	* \brief Metoda pobieraj�ca atrybut.
	*
	* Metoda pobiera atrybut obiektu.
	* \return Metoda zwraca nazw� obiektu.
	*/
	const Tekst& pobierzNazwe() const;

	/**
	* \brief Metoda ustawiaj�ca atrybut.
	*
	* Metoda ustawiaj�ca atrybut obiektu.
	* \param[in] nazwa - Nowa warto�� nazwy obiektu.
	*/
	void ustawNazwe( const Tekst& nazwa );

	/**
	* \brief Metoda pobieraj�ca atrybut.
	*
	* Metoda pobiera atrybut obiektu.
	* \return Metoda zwraca opis obiektu.
	*/
	const Tekst& pobierzOpis() const;

	/**
	* \brief Metoda ustawiaj�ca atrybut.
	*
	* Metoda ustawiaj�ca atrybut obiektu.
	* \param[in] opis - Nowa warto�� opisu obiektu.
	*/
	void ustawOpis( const Tekst& opis );

	/**
	* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
	* \return Napis zwieraj�cy opis klasy.
	*/
	string napis() const override;

private:
	Tekst nazwa_;/// Nazwa obiektu.
	Tekst opis_;/// Opis obiektu.
};
