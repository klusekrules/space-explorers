#pragma once
#include "Logger\LoggerInterface.h"
#include "TypyProste.h"
#include "Poziom.h"
#include "Identyfikator.h"
#include <utility>
using std::pair;
/**
* \brief Klas przechowujaca klucz.
*
* Klasa reprezentuj�ca klucz.
* \author Daniel Wojdak
* \version 1
* \date 18-07-2013
*/
class Klucz:
	virtual public LoggerInterface,
	public PodstawowyInterfejs< pair < Identyfikator, Poziom > >
{
public:

	/**
	* \brief Konstruktor.
	*/
	Klucz();

	/**
	* \brief Konstruktor.
	*
	* Metoda ustawia warto�� atrybut�w na tak� jak jest podana w parametrze konstruktora.
	* \param[in] identyfikator - Warto�� na jak� ma by� ustawiony atrybut identyfikatora klasy.
	* \param[in] poziom - Warto�� na jak� ma by� ustawiony atrybut poziomu klasy.
	*/
	Klucz( const Identyfikator& identyfikator, const Poziom& poziom );

	/**
	* \brief Konstruktor.
	* Metoda ustawia warto�� atrybutu na tak� jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	explicit Klucz( const type_name& wartosc );

	/**
	* \brief Konstruktor kopiuj�cy.
	*
	* Metoda ustawia warto�� atrybutu na tak� jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	Klucz( const Klucz& wartosc );

	/**
	* \brief Destruktor.
	*/
	virtual ~Klucz();
	
	/**
	* \brief Operator r�wno�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator==( const Klucz& wartosc )const;

	/**
	* \brief Operator nierowno�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator!=( const Klucz& wartosc )const;

	/**
	* \brief Operator s�abej mniejszo�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator<( const Klucz& wartosc )const;
	
	/**
	* Funkcja s�u��ca jako podstawa do tworzenia napis�w z opisem klasy.
	* \return Napis zawieraj�cy opis klasy.
	*/
	string napis()const override;
};
