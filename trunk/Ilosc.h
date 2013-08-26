#pragma once
#include "Logger\LoggerInterface.h"
#include "TypyProste.h"
/**
* \brief Klas przechowujaca iloœæ.
*
* Klasa reprezentuj¹ca iloœæ.
* \author Daniel Wojdak
* \version 1
* \date 18-07-2013
*/
class Ilosc:	
	virtual public LoggerInterface,
	public PodstawowyInterfejs<SPG::IloscJednostek>
{
public:

	/**
	* \brief Konstruktor.
	*/
	Ilosc();

	/**
	* \brief Konstruktor.
	*
	* Metoda ustawia wartoœæ atrybutu na tak¹ jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Wartoœæ na jak¹ ma byæ ustawiony atrybut klasy.
	*/
	explicit Ilosc( const type_name& wartosc );

	/**
	* \brief Konstruktor kopiuj¹cy.
	*
	* Metoda ustawia wartoœæ atrybutu na tak¹ jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Wartoœæ na jak¹ ma byæ ustawiony atrybut klasy.
	*/
	Ilosc( const Ilosc& wartosc );

	/**
	* \brief Destruktor.
	*/
	virtual ~Ilosc();

	/**
	* \brief Operator s³abej mniejszoœci.
	*
	* \param[in] wartosc - Wartoœæ porównywana z atrybutem klasy.
	*/
	bool operator<( const Ilosc& wartosc ) const;

	/**
	* \brief Operator s³abej wiêkszoœci.
	*
	* \param[in] wartosc - Wartoœæ porównywana z atrybutem klasy.
	*/
	bool operator>( const Ilosc& wartosc ) const;

	/**
	* \brief Operator równoœci.
	*
	* \param[in] wartosc - Wartoœæ porównywana z atrybutem klasy.
	*/
	bool operator==( const Ilosc& wartosc ) const;

	/**
	* \brief Operator nierównoœci.
	*
	* \param[in] wartosc - Wartoœæ porównywana z atrybutem klasy.
	*/
	bool operator!=( const Ilosc& wartosc ) const;

	/**
	* \brief Operator mniejszoœci.
	*
	* \param[in] wartosc - Wartoœæ porównywana z atrybutem klasy.
	*/
	bool operator<=( const Ilosc& wartosc ) const;

	/**
	* \brief Operator wiêkszoœci.
	*
	* \param[in] wartosc - Wartoœæ porównywana z atrybutem klasy.
	*/
	bool operator>=( const Ilosc& wartosc ) const;

	/**
	* \brief Operator sumy.
	*
	* \param[in] wartosc - Wartoœæ jaka ma byæ dodana do atrybut klasy.
	*/
	Ilosc operator+( const Ilosc& wartosc ) const;

	/**
	* \brief Operator ró¿nicy.
	*
	* \param[in] wartosc - Wartoœæ jaka ma byæ odjêta do atrybut klasy.
	*/
	Ilosc operator-( const Ilosc& wartosc ) const;

	/**
	* \brief Operator przypisania i sumy.
	*
	* \param[in] wartosc - Wartoœæ jaka ma byæ dodana do atrybut klasy.
	*/
	Ilosc& operator+=( const Ilosc& wartosc );

	/**
	* \brief Operator przypisania i ró¿nicy.
	*
	* \param[in] wartosc - Wartoœæ jaka ma byæ odjêta do atrybut klasy.
	*/
	Ilosc& operator-=( const Ilosc& wartosc );

	/**
	* \brief Operator przypisania.
	*
	* \param[in] wartosc - Wartoœæ jaka ma byæ ustawiony atrybut klasy.
	*/
	Ilosc& operator=( const Ilosc& wartosc );

	/**
	* \brief Operator prefiksowej inkrementacji.
	*/
	Ilosc& operator++( );

	/**
	* \brief Operator postfiksowej inkrementacji.
	*/
	Ilosc operator++( int );

	/**
	* \brief Operator mno¿enia.
	*
	* \param[in] wartosc - Wartoœæ jaka ma byæ przemno¿ona przez atrybut klasy.
	*/
	Ilosc operator*( const Ilosc& wartosc )const;

	/**
	* \brief Operator dzielenia.
	*
	* \param[in] wartosc - Wartoœæ jaka ma podzieliæ atrybut klasy.
	*/
	Ilosc operator/( const Ilosc& wartosc )const;

	/**
	* Funkcja s³u¿¹ca jako podstawa do tworzenia napisów z opisem klasy.
	* \return Napis zawieraj¹cy opis klasy.
	*/
	string napis() const override;
};
