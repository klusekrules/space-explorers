#pragma once
#include "Logger\LoggerInterface.h"
#include "TypyProste.h"
/**
* \brief Klas przechowujaca ilosc czasu.
*
* Klasa reprezentuj¹ca ilosc czasu.
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
	* \brief Konstruktor kopiuj¹cy.
	*
	* Metoda ustawia wartoœæ atrybutu na tak¹ jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Wartoœæ na jak¹ ma byæ ustawiony atrybut klasy.
	*/
	Czas( const Czas& wartosc );

	/**
	* \brief Konstruktor.
	*
	* Metoda ustawia wartoœæ atrybutu na tak¹ jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Wartoœæ na jak¹ ma byæ ustawiony atrybut klasy.
	*/
	explicit Czas( const type_name& wartosc );

	/**
	* \brief Destruktor.
	*/
	virtual ~Czas();

	/**
	* \brief Operator równoœci.
	*
	* \param[in] wartosc - Wartoœæ porównywana z atrybutem klasy.
	*/
	bool operator==( const Czas& wartosc )const;

	/**
	* \brief Operator nierownoœci.
	*
	* \param[in] wartosc - Wartoœæ porównywana z atrybutem klasy.
	*/
	bool operator!=( const Czas& wartosc )const;

	/**
	* \brief Operator przypisania.
	*
	* \param[in] wartosc - Wartoœæ jaka ma byæ ustawiony atrybut klasy.
	*/
	Czas& operator=( const Czas& wartosc );

	/**
	* \brief Operator przypisania i sumy.
	*
	* \param[in] wartosc - Wartoœæ jaka ma byæ dodana do atrybut klasy.
	*/
	Czas& operator+=( const Czas& wartosc );

	/**
	* \brief Operator przypisania.
	*
	* \param[in] wartosc - Wartoœæ jaka ma byæ ustawiony atrybut klasy.
	*/
	Czas& operator=( const type_name& wartosc );

	/**
	* Funkcja s³u¿¹ca jako podstawa do tworzenia napisów z opisem klasy.
	* \return Napis zawieraj¹cy opis klasy.
	*/
	string napis() const override;		 
};
