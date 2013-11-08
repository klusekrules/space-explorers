#pragma once
#include "Logger\LoggerInterface.h"
#include "TypyProste.h"

/**
* \brief Klas przechowujaca parametr.
*
* Klasa reprezentuj¹ca parametr.
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
	* Metoda ustawia wartoœæ atrybutu na tak¹ jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Wartoœæ na jak¹ ma byæ ustawiony atrybut klasy.
	*/
	explicit Parametr( const type_name& wartosc );

	/**
	* \brief Konstruktor kopiuj¹cy.
	*
	* Metoda ustawia wartoœæ atrybutu na tak¹ jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Wartoœæ na jak¹ ma byæ ustawiony atrybut klasy.
	*/
	Parametr( const Parametr& wartosc );

	/**
	* \brief Destruktor.
	*/
	virtual ~Parametr();

	/**
	* \brief Operator przypisania.
	*
	* \param[in] wartosc - Wartoœæ na jak¹ ma byæ ustawiony atrybut klasy.
	*/
	Parametr& operator=( const Parametr& wartosc );

	/**
	* Funkcja s³u¿¹ca jako podstawa do tworzenia napisów z opisem klasy.
	* \return Napis zawieraj¹cy opis klasy.
	*/
	std::string napis() const override;
};
