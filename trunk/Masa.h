#pragma once
#include "Logger\LoggerInterface.h"
#include "TypyProste.h"
#include "Fluktuacja.h"
#include "Ilosc.h"

/**
* \brief Klas przechowujaca mas�.
*
* Klasa reprezentuj�ca mas�.
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
	* \brief Konstruktor kopiuj�cy.
	*
	* Metoda ustawia warto�� atrybutu na tak� jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	Masa( const Masa& wartosc );

	/**
	* \brief Konstruktor.
	*
	* Metoda ustawia warto�� atrybutu na tak� jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	explicit Masa( const type_name& wartosc );

	/**
	* \brief Destruktor.
	*/
	virtual ~Masa();

	/**
	* \brief Operator r�wno�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator==( const Masa& wartosc )const;

	/**
	* \brief Operator nier�wno�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator!=( const Masa& wartosc )const;

	/**
	* \brief Operator s�abej mniejszo�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator<( const Masa& wartosc )const;

	/**
	* \brief Operator mniejszo�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator<=( const Masa& wartosc )const;

	/**
	* \brief Operator s�abej wi�kszo�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator>( const Masa& wartosc )const;

	/**
	* \brief Operator wi�kszo�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator>=( const Masa& wartosc )const;

	/**
	* \brief Operator przypisania.
	*
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	Masa& operator=( const Masa& wartosc );

	/**
	* \brief Operator przypisania i r�nicy.
	*
	* \param[in] wartosc - Warto��  jaka ma by� odj�ta do atrybut klasy.
	*/
	Masa& operator-=( const Masa& wartosc );

	/**
	* \brief Operator przypisania i sumy.
	*
	* \param[in] wartosc - Warto��  jaka ma by� dodana do atrybut klasy.
	*/
	Masa& operator+=( const Masa& wartosc );

	/**
	* \brief Operator r�nicy.
	*
	* \param[in] wartosc - Warto�� jaka ma by� odj�ta do atrybut klasy.
	*/
	Masa operator-( const Masa& wartosc )const;

	/**
	* \brief Operator sumy.
	*
	* \param[in] wartosc - Warto�� jaka ma by� dodana do atrybut klasy.
	*/
	Masa operator+( const Masa& wartosc )const;

	/**
	* \brief Operator mno�enia.
	*
	* \param[in] wartosc - Warto�� jaka ma by� przemno�ona przez atrybut klasy.
	*/
	Masa operator*( const Fluktuacja& wartosc )const;

	/**
	* \brief Operator  przypisania i mno�enia.
	*
	* \param[in] wartosc - Warto�� jaka ma by� przemno�ona przez atrybut klasy.
	*/
	Masa& operator*=( const Fluktuacja& wartosc );

	/**
	* \brief Operator mno�enia.
	*
	* \param[in] wartosc - Warto�� jaka ma by� przemno�ona przez atrybut klasy.
	*/
	Masa operator*( const Ilosc& wartosc )const;

	/**
	* \brief Operator  przypisania i mno�enia.
	*
	* \param[in] wartosc - Warto�� jaka ma by� przemno�ona przez atrybut klasy.
	*/
	Masa& operator*=( const Ilosc& wartosc );

	/**
	* Funkcja s�u��ca jako podstawa do tworzenia napis�w z opisem klasy.
	* \return Napis zawieraj�cy opis klasy.
	*/
	string napis() const override; 
};
