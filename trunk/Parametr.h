#pragma once
#include "Logger\LoggerInterface.h"
#include "TypyProste.h"

/**
* \brief Klas przechowujaca parametr.
*
* Klasa reprezentuj�ca parametr.
* \author Daniel Wojdak
* \version 1
* \date 19-07-2013
*/
class Parametr:
	virtual public LoggerInterface,
	public PodstawowyInterfejs<SPG::Parametr>
{
public:

	/**
	* \brief Konstruktor.
	*/
	Parametr();

	/**
	* \brief Konstruktor.
	*
	* Metoda ustawia warto�� atrybutu na tak� jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	explicit Parametr( const type_name& wartosc );

	/**
	* \brief Konstruktor kopiuj�cy.
	*
	* Metoda ustawia warto�� atrybutu na tak� jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	Parametr( const Parametr& wartosc );

	/**
	* \brief Destruktor.
	*/
	virtual ~Parametr();

	/**
	* \brief Operator przypisania.
	*
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	Parametr& operator=( const Parametr& wartosc );

	/**
	* Funkcja s�u��ca jako podstawa do tworzenia napis�w z opisem klasy.
	* \return Napis zawieraj�cy opis klasy.
	*/
	std::string napis() const override;
};
