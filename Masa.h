#pragma once
#include "Logger\LoggerInterface.h"
#include "TypyProste.h"
#include "Fluktuacja.h"
#include "Ilosc.h"

/**
* \brief Klas przechowujaca masê.
*
* Klasa reprezentuj¹ca masê.
* \author Daniel Wojdak
* \version 1
* \date 19-07-2013
*/
class Masa:
	virtual public LoggerInterface,
	public PodstawowyInterfejs<SPG::Masa>
{
public:

	/**
	* \brief Konstruktor.
	*/
	Masa();

	/**
	* \brief Konstruktor kopiuj¹cy.
	*
	* Metoda ustawia wartoœæ atrybutu na tak¹ jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Wartoœæ na jak¹ ma byæ ustawiony atrybut klasy.
	*/
	Masa( const Masa& wartosc );

	/**
	* \brief Konstruktor.
	*
	* Metoda ustawia wartoœæ atrybutu na tak¹ jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Wartoœæ na jak¹ ma byæ ustawiony atrybut klasy.
	*/
	explicit Masa( const type_name& wartosc );

	/**
	* \brief Destruktor.
	*/
	virtual ~Masa();

	/**
	* \brief Operator równoœci.
	*
	* \param[in] wartosc - Wartoœæ porównywana z atrybutem klasy.
	*/
	bool operator==( const Masa& wartosc )const;

	/**
	* \brief Operator nierównoœci.
	*
	* \param[in] wartosc - Wartoœæ porównywana z atrybutem klasy.
	*/
	bool operator!=( const Masa& wartosc )const;

	/**
	* \brief Operator s³abej mniejszoœci.
	*
	* \param[in] wartosc - Wartoœæ porównywana z atrybutem klasy.
	*/
	bool operator<( const Masa& wartosc )const;

	/**
	* \brief Operator mniejszoœci.
	*
	* \param[in] wartosc - Wartoœæ porównywana z atrybutem klasy.
	*/
	bool operator<=( const Masa& wartosc )const;

	/**
	* \brief Operator s³abej wiêkszoœci.
	*
	* \param[in] wartosc - Wartoœæ porównywana z atrybutem klasy.
	*/
	bool operator>( const Masa& wartosc )const;

	/**
	* \brief Operator wiêkszoœci.
	*
	* \param[in] wartosc - Wartoœæ porównywana z atrybutem klasy.
	*/
	bool operator>=( const Masa& wartosc )const;

	/**
	* \brief Operator przypisania.
	*
	* \param[in] wartosc - Wartoœæ na jak¹ ma byæ ustawiony atrybut klasy.
	*/
	Masa& operator=( const Masa& wartosc );

	/**
	* \brief Operator przypisania i ró¿nicy.
	*
	* \param[in] wartosc - Wartoœæ  jaka ma byæ odjêta do atrybut klasy.
	*/
	Masa& operator-=( const Masa& wartosc );

	/**
	* \brief Operator przypisania i sumy.
	*
	* \param[in] wartosc - Wartoœæ  jaka ma byæ dodana do atrybut klasy.
	*/
	Masa& operator+=( const Masa& wartosc );

	/**
	* \brief Operator ró¿nicy.
	*
	* \param[in] wartosc - Wartoœæ jaka ma byæ odjêta do atrybut klasy.
	*/
	Masa operator-( const Masa& wartosc )const;

	/**
	* \brief Operator sumy.
	*
	* \param[in] wartosc - Wartoœæ jaka ma byæ dodana do atrybut klasy.
	*/
	Masa operator+( const Masa& wartosc )const;

	/**
	* \brief Operator mno¿enia.
	*
	* \param[in] wartosc - Wartoœæ jaka ma byæ przemno¿ona przez atrybut klasy.
	*/
	Masa operator*( const Fluktuacja& wartosc )const;

	/**
	* \brief Operator  przypisania i mno¿enia.
	*
	* \param[in] wartosc - Wartoœæ jaka ma byæ przemno¿ona przez atrybut klasy.
	*/
	Masa& operator*=( const Fluktuacja& wartosc );

	/**
	* \brief Operator mno¿enia.
	*
	* \param[in] wartosc - Wartoœæ jaka ma byæ przemno¿ona przez atrybut klasy.
	*/
	Masa operator*( const Ilosc& wartosc )const;

	/**
	* \brief Operator  przypisania i mno¿enia.
	*
	* \param[in] wartosc - Wartoœæ jaka ma byæ przemno¿ona przez atrybut klasy.
	*/
	Masa& operator*=( const Ilosc& wartosc );

	/**
	* Funkcja s³u¿¹ca jako podstawa do tworzenia napisów z opisem klasy.
	* \return Napis zawieraj¹cy opis klasy.
	*/
	string napis() const override; 
};
