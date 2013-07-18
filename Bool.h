#pragma once
#include "Logger\LoggerInterface.h"
#include "TypyProste.h"
/**
* \brief Klas typu logicznego.
*
* Klasa reprezentuj�ca typ logiczny.
* \author Daniel Wojdak
* \version 1
* \date 18-07-2013
*/
class Bool:
	virtual public LoggerInterface,
	public PodstawowyInterfejs<bool>
{
public:	

	/**
	* \brief Konstruktor.
	*/
	Bool();

	/**
	* \brief Konstruktor kopiuj�cy.
	* Metoda ustawia warto�� atrybutu na tak� jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	Bool( const Bool& wartosc );

	/**
	* \brief Konstruktor.
	* Metoda ustawia warto�� atrybutu na tak� jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	explicit Bool( const type_name& wartosc );

	/**
	* \brief Destruktor.
	*/
	virtual ~Bool();

	/**
	* \brief Operator r�wno�ci.
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator==( const Bool& wartosc )const;

	/**
	* \brief Operator nier�wno�ci.
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator!=( const Bool& wartosc )const;

	/**
	* \brief Operator przypisania.
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	Bool& operator=( const Bool& wartosc );

	/**
	* \brief Operator przypisania.
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	Bool& operator=( const type_name& wartosc );

	/**
	* Funkcja s�u��ca jako podstawa do tworzenia napis�w z opisem klasy.
	* \return Napis zawieraj�cy opis klasy.
	*/
	string napis() const override; 
};
