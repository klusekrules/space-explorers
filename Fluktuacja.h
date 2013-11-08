#pragma once
#include "Logger\LoggerInterface.h"
#include "TypyProste.h"
/**
* \brief Klas przechowujaca fluktuacje.
*
* Klasa reprezentuj�ca fluktuacje.
* \author Daniel Wojdak
* \version 1
* \date 18-07-2013
*/
class Fluktuacja:
	virtual public LoggerInterface,
	public PodstawowyInterfejs<SPG::Fluktuacja>
{
public:
	static const SPG::Fluktuacja MIN;
	static const SPG::Fluktuacja MAX;
	/**
	* \brief Konstruktor.
	*/
	Fluktuacja();

	/**
	* \brief Konstruktor kopiuj�cy.
	*
	* Metoda ustawia warto�� atrybutu na tak� jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	Fluktuacja( const Fluktuacja& wartosc );

	/**
	* \brief Konstruktor.
	*
	* Metoda ustawia warto�� atrybutu na tak� jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	explicit Fluktuacja( const type_name& wartosc );

	/**
	* \brief Destruktor.
	*/
	virtual ~Fluktuacja();

	/**
	* \brief Operator r�wno�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator==( const Fluktuacja& wartosc )const;

	/**
	* \brief Operator nier�wno�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator!=( const Fluktuacja& wartosc )const;

	/**
	* \brief Operator s�abej mniejszo�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator<( const Fluktuacja& wartosc )const;

	/**
	* \brief Operator s�abej wi�kszo�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator>( const Fluktuacja& wartosc )const;

	/**
	* \brief Operator mniejszo�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator<=( const Fluktuacja& wartosc )const;

	/**
	* \brief Operator wi�kszo�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator>=( const Fluktuacja& wartosc )const;

	/**
	* \brief Operator przypisania.
	*
	* \param[in] wartosc - Warto�� jaka ma by� ustawiony atrybut klasy.
	*/
	Fluktuacja& operator=( const Fluktuacja& wartosc );

	/**
	* \brief Operator przypisania i r�nicy.
	*
	* \param[in] wartosc - Warto�� jaka ma by� odj�ta do atrybut klasy.
	*/
	Fluktuacja& operator-=( const Fluktuacja& wartosc );

	/**
	* \brief Operator przypisania i sumy.
	*
	* \param[in] wartosc - Warto�� jaka ma by� dodana do atrybut klasy.
	*/
	Fluktuacja& operator+=( const Fluktuacja& wartosc );

	/**
	* \brief Operator r�nicy.
	*
	* \param[in] wartosc - Warto�� jaka ma by� odj�ta do atrybut klasy.
	*/
	Fluktuacja operator-( const Fluktuacja& wartosc )const;

	/**
	* \brief Operator sumy.
	*
	* \param[in] wartosc - Warto�� jaka ma by� dodana do atrybut klasy.
	*/
	Fluktuacja operator+( const Fluktuacja& wartosc )const;

	/**
	* Funkcja s�u��ca jako podstawa do tworzenia napis�w z opisem klasy.
	* \return Napis zawieraj�cy opis klasy.
	*/
	std::string napis() const override; 
};
