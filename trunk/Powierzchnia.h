#pragma once
#include "Logger\LoggerInterface.h"
#include "TypyProste.h"
#include "Fluktuacja.h"
#include "Ilosc.h"

/**
* \brief Klas przechowujaca powierzchni�.
*
* Klasa reprezentuj�ca powierzchni�.
* \author Daniel Wojdak
* \version 1
* \date 19-07-2013
*/
class Powierzchnia:	
	virtual public LoggerInterface,
	public PodstawowyInterfejs<SPG::Powierzchnia>
{
public:

	/**
	* \brief Konstruktor.
	*/
	Powierzchnia();

	/**
	* \brief Konstruktor kopiuj�cy.
	*
	* Metoda ustawia warto�� atrybutu na tak� jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	Powierzchnia( const Powierzchnia& wartosc );

	/**
	* \brief Konstruktor.
	*
	* Metoda ustawia warto�� atrybutu na tak� jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	explicit Powierzchnia( const type_name& wartosc );

	/**
	* \brief Destruktor.
	*/
	virtual ~Powierzchnia();

	/**
	* \brief Operator r�wno�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator==( const Powierzchnia& wartosc )const;

	/**
	* \brief Operator nier�wno�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator!=( const Powierzchnia& wartosc )const;

	/**
	* \brief Operator s�abej mniejszo�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator<( const Powierzchnia& wartosc )const;

	/**
	* \brief Operator mniejszo�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator<=( const Powierzchnia& wartosc )const;

	/**
	* \brief Operator s�abej wi�kszo�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator>( const Powierzchnia& wartosc )const;

	/**
	* \brief Operator wi�kszo�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator>=( const Powierzchnia& wartosc )const;

	/**
	* \brief Operator przypisania.
	*
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	Powierzchnia& operator=( const Powierzchnia& wartosc );

	/**
	* \brief Operator przypisania i r�nicy.
	*
	* \param[in] wartosc - Warto��  jaka ma by� odj�ta do atrybut klasy.
	*/
	Powierzchnia& operator-=( const Powierzchnia& wartosc );

	/**
	* \brief Operator przypisania i sumy.
	*
	* \param[in] wartosc - Warto��  jaka ma by� dodana do atrybut klasy.
	*/
	Powierzchnia& operator+=( const Powierzchnia& wartosc );

	/**
	* \brief Operator r�nicy.
	*
	* \param[in] wartosc - Warto�� jaka ma by� odj�ta do atrybut klasy.
	*/
	Powierzchnia operator-( const Powierzchnia& wartosc )const;

	/**
	* \brief Operator sumy.
	*
	* \param[in] wartosc - Warto�� jaka ma by� dodana do atrybut klasy.
	*/
	Powierzchnia operator+( const Powierzchnia& wartosc )const;

	/**
	* \brief Operator mno�enia.
	*
	* \param[in] wartosc - Warto�� jaka ma by� przemno�ona przez atrybut klasy.
	*/
	Powierzchnia operator*( const Fluktuacja& wartosc )const;

	/**
	* \brief Operator  przypisania i mno�enia.
	*
	* \param[in] wartosc - Warto�� jaka ma by� przemno�ona przez atrybut klasy.
	*/
	Powierzchnia& operator*=( const Fluktuacja& wartosc );

	/**
	* \brief Operator mno�enia.
	*
	* \param[in] wartosc - Warto�� jaka ma by� przemno�ona przez atrybut klasy.
	*/
	Powierzchnia operator*( const Ilosc& wartosc )const;

	/**
	* \brief Operator  przypisania i mno�enia.
	*
	* \param[in] wartosc - Warto�� jaka ma by� przemno�ona przez atrybut klasy.
	*/
	Powierzchnia& operator*=( const Ilosc& wartosc );

	/**
	* Funkcja s�u��ca jako podstawa do tworzenia napis�w z opisem klasy.
	* \return Napis zawieraj�cy opis klasy.
	*/
	std::string napis() const override; 
};
