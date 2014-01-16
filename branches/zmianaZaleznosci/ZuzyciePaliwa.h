#pragma once
#include "Logger\LoggerInterface.h"
#include "TypyProste.h"

/**
* \brief Klas przechowujaca zau¿ycie paliwa.
*
* Klasa reprezentuj¹ca zau¿ycie paliwa.
* \author Daniel Wojdak
* \version 1
* \date 19-07-2013
*/
class ZuzyciePaliwa:
	virtual public LoggerInterface,
	public PodstawowyInterfejs<SPG::ZuzyciePaliwa>
{
public:

	/**
	* \brief Konstruktor.
	*/
	ZuzyciePaliwa();

	/**
	* \brief Konstruktor kopiuj¹cy.
	*
	* Metoda ustawia wartoœæ atrybutu na tak¹ jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Wartoœæ na jak¹ ma byæ ustawiony atrybut klasy.
	*/
	ZuzyciePaliwa( const ZuzyciePaliwa& wartosc );

	/**
	* \brief Konstruktor.
	*
	* Metoda ustawia wartoœæ atrybutu na tak¹ jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Wartoœæ na jak¹ ma byæ ustawiony atrybut klasy.
	*/
	explicit ZuzyciePaliwa( const type_name& wartosc );

	/**
	* \brief Destruktor.
	*/
	virtual ~ZuzyciePaliwa();

	/**
	* \brief Operator równoœci.
	*
	* \param[in] wartosc - Wartoœæ porównywana z atrybutem klasy.
	*/
	bool operator==( const ZuzyciePaliwa& wartosc )const;

	/**
	* \brief Operator nierównoœci.
	*
	* \param[in] wartosc - Wartoœæ porównywana z atrybutem klasy.
	*/
	bool operator!=( const ZuzyciePaliwa& wartosc )const;

	/**
	* \brief Operator s³abej mniejszoœci.
	*
	* \param[in] wartosc - Wartoœæ porównywana z atrybutem klasy.
	*/
	bool operator<( const ZuzyciePaliwa& wartosc )const;

	/**
	* \brief Operator mniejszoœci.
	*
	* \param[in] wartosc - Wartoœæ porównywana z atrybutem klasy.
	*/
	bool operator<=( const ZuzyciePaliwa& wartosc )const;

	/**
	* \brief Operator s³abej wiêkszoœci.
	*
	* \param[in] wartosc - Wartoœæ porównywana z atrybutem klasy.
	*/
	bool operator>( const ZuzyciePaliwa& wartosc )const;

	/**
	* \brief Operator wiêkszoœci.
	*
	* \param[in] wartosc - Wartoœæ porównywana z atrybutem klasy.
	*/
	bool operator>=( const ZuzyciePaliwa& wartosc )const;

	/**
	* \brief Operator przypisania.
	*
	* \param[in] wartosc - Wartoœæ na jak¹ ma byæ ustawiony atrybut klasy.
	*/
	ZuzyciePaliwa& operator=( const ZuzyciePaliwa& wartosc );

	/**
	* \brief Operator przypisania i ró¿nicy.
	*
	* \param[in] wartosc - Wartoœæ  jaka ma byæ odjêta do atrybut klasy.
	*/
	ZuzyciePaliwa& operator-=( const ZuzyciePaliwa& wartosc );

	/**
	* \brief Operator przypisania i sumy.
	*
	* \param[in] wartosc - Wartoœæ  jaka ma byæ dodana do atrybut klasy.
	*/
	ZuzyciePaliwa& operator+=( const ZuzyciePaliwa& wartosc );

	/**
	* \brief Operator ró¿nicy.
	*
	* \param[in] wartosc - Wartoœæ jaka ma byæ odjêta do atrybut klasy.
	*/
	ZuzyciePaliwa operator-( const ZuzyciePaliwa& wartosc )const;

	/**
	* \brief Operator sumy.
	*
	* \param[in] wartosc - Wartoœæ jaka ma byæ dodana do atrybut klasy.
	*/
	ZuzyciePaliwa operator+( const ZuzyciePaliwa& wartosc )const;

	/**
	* Funkcja s³u¿¹ca jako podstawa do tworzenia napisów z opisem klasy.
	* \return Napis zawieraj¹cy opis klasy.
	*/
	std::string napis() const override; 
};
