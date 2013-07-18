#pragma once
#include "Logger\LoggerInterface.h"
#include "TypyProste.h"
/**
* \brief Klas typu logicznego.
*
* Klasa reprezentuj¹ca typ logiczny.
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
	* \brief Konstruktor kopiuj¹cy.
	* Metoda ustawia wartoœæ atrybutu na tak¹ jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Wartoœæ na jak¹ ma byæ ustawiony atrybut klasy.
	*/
	Bool( const Bool& wartosc );

	/**
	* \brief Konstruktor.
	* Metoda ustawia wartoœæ atrybutu na tak¹ jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Wartoœæ na jak¹ ma byæ ustawiony atrybut klasy.
	*/
	explicit Bool( const type_name& wartosc );

	/**
	* \brief Destruktor.
	*/
	virtual ~Bool();

	/**
	* \brief Operator równoœci.
	* \param[in] wartosc - Wartoœæ porównywana z atrybutem klasy.
	*/
	bool operator==( const Bool& wartosc )const;

	/**
	* \brief Operator nierównoœci.
	* \param[in] wartosc - Wartoœæ porównywana z atrybutem klasy.
	*/
	bool operator!=( const Bool& wartosc )const;

	/**
	* \brief Operator przypisania.
	* \param[in] wartosc - Wartoœæ na jak¹ ma byæ ustawiony atrybut klasy.
	*/
	Bool& operator=( const Bool& wartosc );

	/**
	* \brief Operator przypisania.
	* \param[in] wartosc - Wartoœæ na jak¹ ma byæ ustawiony atrybut klasy.
	*/
	Bool& operator=( const type_name& wartosc );

	/**
	* Funkcja s³u¿¹ca jako podstawa do tworzenia napisów z opisem klasy.
	* \return Napis zawieraj¹cy opis klasy.
	*/
	string napis() const override; 
};
