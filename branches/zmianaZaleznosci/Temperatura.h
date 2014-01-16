#pragma once
#include "Logger\LoggerInterface.h" 
#include "TypyProste.h"

/**
* \brief Klas przechowujaca temperatur�.
*
* Klasa reprezentuj�ca temperatur� w Kelwinach.
* \author Daniel Wojdak
* \version 1
* \date 15-10-2013
*/
class Temperatura:
	virtual public LoggerInterface,
	public PodstawowyInterfejs< SPG::Temperatura >
{
public:	

	/**
	* \brief Konstruktor.
	*/
	Temperatura();

	/**
	* \brief Konstruktor kopiuj�cy.
	*
	* Metoda ustawia warto�� atrybutu na tak� jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	Temperatura( const Temperatura& wartosc );

	/**
	* \brief Konstruktor.
	*
	* Metoda ustawia warto�� atrybutu na tak� jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	explicit Temperatura( const type_name& wartosc );

	/**
	* \brief Destruktor.
	*/
	virtual ~Temperatura();
	
	/**
	* \brief Operator r�wno�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator==( const Temperatura& wartosc )const;

	/**
	* \brief Operator nier�wno�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator!=( const Temperatura& wartosc )const;

	/**
	* \brief Operator przypisania.
	*
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	Temperatura& operator=( const Temperatura& wartosc );

	/**
	* Funkcja s�u��ca jako podstawa do tworzenia napis�w z opisem klasy.
	* \return Napis zawieraj�cy opis klasy.
	*/
	std::string napis() const override;

};

