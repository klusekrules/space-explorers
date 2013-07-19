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
* Klasa reprezentuj¹ca klucz.
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
	* Metoda ustawia wartoœæ atrybutów na tak¹ jak jest podana w parametrze konstruktora.
	* \param[in] identyfikator - Wartoœæ na jak¹ ma byæ ustawiony atrybut identyfikatora klasy.
	* \param[in] poziom - Wartoœæ na jak¹ ma byæ ustawiony atrybut poziomu klasy.
	*/
	Klucz( const Identyfikator& identyfikator, const Poziom& poziom );

	/**
	* \brief Konstruktor.
	* Metoda ustawia wartoœæ atrybutu na tak¹ jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Wartoœæ na jak¹ ma byæ ustawiony atrybut klasy.
	*/
	explicit Klucz( const type_name& wartosc );

	/**
	* \brief Konstruktor kopiuj¹cy.
	*
	* Metoda ustawia wartoœæ atrybutu na tak¹ jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Wartoœæ na jak¹ ma byæ ustawiony atrybut klasy.
	*/
	Klucz( const Klucz& wartosc );

	/**
	* \brief Destruktor.
	*/
	virtual ~Klucz();
	
	/**
	* \brief Operator równoœci.
	*
	* \param[in] wartosc - Wartoœæ porównywana z atrybutem klasy.
	*/
	bool operator==( const Klucz& wartosc )const;

	/**
	* \brief Operator nierownoœci.
	*
	* \param[in] wartosc - Wartoœæ porównywana z atrybutem klasy.
	*/
	bool operator!=( const Klucz& wartosc )const;

	/**
	* \brief Operator s³abej mniejszoœci.
	*
	* \param[in] wartosc - Wartoœæ porównywana z atrybutem klasy.
	*/
	bool operator<( const Klucz& wartosc )const;
	
	/**
	* Funkcja s³u¿¹ca jako podstawa do tworzenia napisów z opisem klasy.
	* \return Napis zawieraj¹cy opis klasy.
	*/
	string napis()const override;
};
