#pragma once
#include "Logger\LoggerInterface.h"
#include "TypyProste.h"

/**
* \brief Klas przechowujaca tekst.
*
* Klasa reprezentuj�ca tekst.
* \author Daniel Wojdak
* \version 1
* \date 19-07-2013
*/
class Tekst:
	virtual public LoggerInterface,
	public PodstawowyInterfejs<SPG::Tekst>
{
private:

	/**
	* \brief Metoda pomocnicza
	*
	* Metoda skleja cudzys��w z napisem i zwraca otrzymany napis. Metoda nie modyfikuje atrybutru.
	* \return Napis otoczony cudzys�owem.
	*/
	type_name dodajCudzyslow() const;

public:

	/**
	* \brief Konstruktor.
	*/
	Tekst();

	/**
	* \brief Konstruktor.
	*
	* Metoda ustawia warto�� atrybutu na tak� jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	Tekst( const type_name& wartosc );

	/**
	* \brief Konstruktor kopiuj�cy.
	*
	* Metoda ustawia warto�� atrybutu na tak� jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	Tekst( const Tekst& wartosc );

	/**
	* \brief Destruktor.
	*/
	virtual ~Tekst();

	/**
	* \brief Operator sumy.
	*
	* \param[in] wartosc - Napis jaki ma by� dodany do atrybut klasy.
	*/
	Tekst operator+( const Tekst& wartosc ) const;

	/**
	* \brief Operator przypisania i sumy.
	*
	* \param[in] wartosc - Napis jaki ma by� dodany do atrybut klasy.
	*/
	Tekst& operator+=( const Tekst& wartosc );

	/**
	* \brief Operator przypisania.
	*
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	Tekst& operator=( const Tekst& wartosc );

	/**
	* \brief Operator r�wno�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator==( const Tekst& wartosc ) const;

	/**
	* \brief Operator nier�wno�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator!=( const Tekst& wartosc ) const;

	/**
	* Metoda sprawdza czy napis jest pusty.
	* \return Warto�� true je�eli napis jest pusty, false w przeciwnym wypadku.
	*/
	bool isEmpty() const;

	/**
	* Funkcja s�u��ca jako podstawa do tworzenia napis�w z opisem klasy.
	* \return Napis zawieraj�cy opis klasy.
	*/
	string napis()const override;
};
