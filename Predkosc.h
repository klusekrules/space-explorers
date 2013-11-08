#pragma once
#include "Logger\LoggerInterface.h"
#include "TypyProste.h"

/**
* \brief Klas przechowujaca pr�dko��.
*
* Klasa reprezentuj�ca pr�dko��.
* \author Daniel Wojdak
* \version 1
* \date 19-07-2013
*/
class Predkosc:
	virtual public LoggerInterface,
	public PodstawowyInterfejs<SPG::Predkosc>
{
public:	

	/**
	* \brief Konstruktor.
	*/
	Predkosc();

	/**
	* \brief Konstruktor kopiuj�cy.
	*
	* Metoda ustawia warto�� atrybutu na tak� jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	Predkosc( const Predkosc& wartosc );

	/**
	* \brief Konstruktor.
	*
	* Metoda ustawia warto�� atrybutu na tak� jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	explicit Predkosc( const type_name& wartosc );

	/**
	* \brief Destruktor.
	*/
	virtual ~Predkosc();

	/**
	* \brief Operator r�wno�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator==( const Predkosc& wartosc )const;

	/**
	* \brief Operator nier�wno�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator!=( const Predkosc& wartosc )const;

	/**
	* \brief Operator s�abej mniejszo�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator<( const Predkosc& wartosc )const;

	/**
	* \brief Operator mniejszo�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator<=( const Predkosc& wartosc )const;

	/**
	* \brief Operator s�abej wi�kszo�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator>( const Predkosc& wartosc )const;

	/**
	* \brief Operator wi�kszo�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator>=( const Predkosc& wartosc )const;

	/**
	* \brief Operator przypisania.
	*
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	Predkosc& operator=( const Predkosc& wartosc );

	/**
	* \brief Operator przypisania i r�nicy.
	*
	* \param[in] wartosc - Warto��  jaka ma by� odj�ta do atrybut klasy.
	*/
	Predkosc& operator-=( const Predkosc& wartosc );

	/**
	* \brief Operator przypisania i sumy.
	*
	* \param[in] wartosc - Warto��  jaka ma by� dodana do atrybut klasy.
	*/
	Predkosc& operator+=( const Predkosc& wartosc );

	/**
	* \brief Operator r�nicy.
	*
	* \param[in] wartosc - Warto�� jaka ma by� odj�ta do atrybut klasy.
	*/
	Predkosc operator-( const Predkosc& wartosc )const;

	/**
	* \brief Operator sumy.
	*
	* \param[in] wartosc - Warto�� jaka ma by� dodana do atrybut klasy.
	*/
	Predkosc operator+( const Predkosc& wartosc )const;

	/**
	* Funkcja s�u��ca jako podstawa do tworzenia napis�w z opisem klasy.
	* \return Napis zawieraj�cy opis klasy.
	*/
	std::string napis() const override; 
};
