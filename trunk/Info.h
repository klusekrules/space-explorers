#pragma once
#include "Bazowa.h"
#include "Tekst.h"
#include "Identyfikator.h"
#include "Wymagania.h"
#include "WyjatekParseraXML.h"

/**
* \brief Klasa bazowa obiektu opisuj¹cego.
*
* Klasa bazowa dla obiektu opisuj¹cego. Zawiera podstawowy opis obiektu. Zawiera wymagania obiektu. 
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
	* Konstruktor tworz¹cy obiekt na podstawie wêz³a xml.
	* \param[in] wezel - Wêze³ na podstawie, którego jest tworzony obiekt.
	*/
	explicit Info( TiXmlElement * wezel ) throw(WyjatekParseraXML);

	/**
	* \brief Destruktor.
	*/
	virtual ~Info();

	/**
	* \brief Metoda pobieraj¹ca atrybut.
	*
	* Metoda pobiera atrybut obiektu.
	* \return Metoda zwraca nazwê obiektu.
	*/
	const Tekst& pobierzNazwe() const;

	/**
	* \brief Metoda ustawiaj¹ca atrybut.
	*
	* Metoda ustawiaj¹ca atrybut obiektu.
	* \param[in] nazwa - Nowa wartoœæ nazwy obiektu.
	*/
	void ustawNazwe( const Tekst& nazwa );

	/**
	* \brief Metoda pobieraj¹ca atrybut.
	*
	* Metoda pobiera atrybut obiektu.
	* \return Metoda zwraca opis obiektu.
	*/
	const Tekst& pobierzOpis() const;

	/**
	* \brief Metoda ustawiaj¹ca atrybut.
	*
	* Metoda ustawiaj¹ca atrybut obiektu.
	* \param[in] opis - Nowa wartoœæ opisu obiektu.
	*/
	void ustawOpis( const Tekst& opis );

	/**
	* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
	* \return Napis zwieraj¹cy opis klasy.
	*/
	string napis() const override;

private:
	Tekst nazwa_;/// Nazwa obiektu.
	Tekst opis_;/// Opis obiektu.
};
