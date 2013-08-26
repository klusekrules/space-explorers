#pragma once
#include "Logger\LoggerInterface.h"
#include "TypyProste.h"
/**
* \brief Klas przechowujaca ilo��.
*
* Klasa reprezentuj�ca ilo��.
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
	* Metoda ustawia warto�� atrybutu na tak� jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	explicit Ilosc( const type_name& wartosc );

	/**
	* \brief Konstruktor kopiuj�cy.
	*
	* Metoda ustawia warto�� atrybutu na tak� jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	Ilosc( const Ilosc& wartosc );

	/**
	* \brief Destruktor.
	*/
	virtual ~Ilosc();

	/**
	* \brief Operator s�abej mniejszo�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator<( const Ilosc& wartosc ) const;

	/**
	* \brief Operator s�abej wi�kszo�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator>( const Ilosc& wartosc ) const;

	/**
	* \brief Operator r�wno�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator==( const Ilosc& wartosc ) const;

	/**
	* \brief Operator nier�wno�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator!=( const Ilosc& wartosc ) const;

	/**
	* \brief Operator mniejszo�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator<=( const Ilosc& wartosc ) const;

	/**
	* \brief Operator wi�kszo�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator>=( const Ilosc& wartosc ) const;

	/**
	* \brief Operator sumy.
	*
	* \param[in] wartosc - Warto�� jaka ma by� dodana do atrybut klasy.
	*/
	Ilosc operator+( const Ilosc& wartosc ) const;

	/**
	* \brief Operator r�nicy.
	*
	* \param[in] wartosc - Warto�� jaka ma by� odj�ta do atrybut klasy.
	*/
	Ilosc operator-( const Ilosc& wartosc ) const;

	/**
	* \brief Operator przypisania i sumy.
	*
	* \param[in] wartosc - Warto�� jaka ma by� dodana do atrybut klasy.
	*/
	Ilosc& operator+=( const Ilosc& wartosc );

	/**
	* \brief Operator przypisania i r�nicy.
	*
	* \param[in] wartosc - Warto�� jaka ma by� odj�ta do atrybut klasy.
	*/
	Ilosc& operator-=( const Ilosc& wartosc );

	/**
	* \brief Operator przypisania.
	*
	* \param[in] wartosc - Warto�� jaka ma by� ustawiony atrybut klasy.
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
	* \brief Operator mno�enia.
	*
	* \param[in] wartosc - Warto�� jaka ma by� przemno�ona przez atrybut klasy.
	*/
	Ilosc operator*( const Ilosc& wartosc )const;

	/**
	* \brief Operator dzielenia.
	*
	* \param[in] wartosc - Warto�� jaka ma podzieli� atrybut klasy.
	*/
	Ilosc operator/( const Ilosc& wartosc )const;

	/**
	* Funkcja s�u��ca jako podstawa do tworzenia napis�w z opisem klasy.
	* \return Napis zawieraj�cy opis klasy.
	*/
	string napis() const override;
};
