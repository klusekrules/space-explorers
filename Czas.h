#pragma once
#include "Logger\LoggerInterface.h"
#include "TypyProste.h"
/**
* \brief Klas przechowujaca ilosc czasu.
*
* Klasa reprezentuj�ca ilosc czasu.
* \author Daniel Wojdak
* \version 1
* \date 18-07-2013
*/
class Czas:
	public LoggerInterface,
	public PodstawowyInterfejs< SPG::Czas >
{
public:	

	/**
	* \brief Konstruktor.
	*/
	Czas();

	/**
	* \brief Konstruktor kopiuj�cy.
	*
	* Metoda ustawia warto�� atrybutu na tak� jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	Czas( const Czas& wartosc );

	/**
	* \brief Konstruktor.
	*
	* Metoda ustawia warto�� atrybutu na tak� jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	explicit Czas( const type_name& wartosc );

	/**
	* \brief Destruktor.
	*/
	virtual ~Czas();

	/**
	* \brief Operator r�wno�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator==( const Czas& wartosc )const;

	/**
	* \brief Operator nierowno�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator!=( const Czas& wartosc )const;

	/**
	* \brief Operator przypisania.
	*
	* \param[in] wartosc - Warto�� jaka ma by� ustawiony atrybut klasy.
	*/
	Czas& operator=( const Czas& wartosc );

	/**
	* \brief Operator przypisania i sumy.
	*
	* \param[in] wartosc - Warto�� jaka ma by� dodana do atrybut klasy.
	*/
	Czas& operator+=( const Czas& wartosc );

	/**
	* \brief Operator przypisania.
	*
	* \param[in] wartosc - Warto�� jaka ma by� ustawiony atrybut klasy.
	*/
	Czas& operator=( const type_name& wartosc );

	/**
	* Funkcja s�u��ca jako podstawa do tworzenia napis�w z opisem klasy.
	* \return Napis zawieraj�cy opis klasy.
	*/
	string napis() const override;		 
};
