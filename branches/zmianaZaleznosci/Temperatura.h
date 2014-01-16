#pragma once
#include "Logger\LoggerInterface.h" 
#include "TypyProste.h"

/**
* \brief Klas przechowujaca temperaturê.
*
* Klasa reprezentuj¹ca temperaturê w Kelwinach.
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
	* \brief Konstruktor kopiuj¹cy.
	*
	* Metoda ustawia wartoœæ atrybutu na tak¹ jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Wartoœæ na jak¹ ma byæ ustawiony atrybut klasy.
	*/
	Temperatura( const Temperatura& wartosc );

	/**
	* \brief Konstruktor.
	*
	* Metoda ustawia wartoœæ atrybutu na tak¹ jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Wartoœæ na jak¹ ma byæ ustawiony atrybut klasy.
	*/
	explicit Temperatura( const type_name& wartosc );

	/**
	* \brief Destruktor.
	*/
	virtual ~Temperatura();
	
	/**
	* \brief Operator równoœci.
	*
	* \param[in] wartosc - Wartoœæ porównywana z atrybutem klasy.
	*/
	bool operator==( const Temperatura& wartosc )const;

	/**
	* \brief Operator nierównoœci.
	*
	* \param[in] wartosc - Wartoœæ porównywana z atrybutem klasy.
	*/
	bool operator!=( const Temperatura& wartosc )const;

	/**
	* \brief Operator przypisania.
	*
	* \param[in] wartosc - Wartoœæ na jak¹ ma byæ ustawiony atrybut klasy.
	*/
	Temperatura& operator=( const Temperatura& wartosc );

	/**
	* Funkcja s³u¿¹ca jako podstawa do tworzenia napisów z opisem klasy.
	* \return Napis zawieraj¹cy opis klasy.
	*/
	std::string napis() const override;

};

