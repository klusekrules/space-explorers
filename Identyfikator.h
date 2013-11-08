#pragma once
#include "Logger\LoggerInterface.h"
#include "TypyProste.h"
#include "Ilosc.h"
/**
* \brief Klas przechowujaca identyfikator.
*
* Klasa reprezentuj�ca identyfikator.
* \author Daniel Wojdak
* \version 1
* \date 18-07-2013
*/
class Identyfikator :
	virtual public LoggerInterface,
	public PodstawowyInterfejs<SPG::Identyfikator>
{
public:
	/**
	* \brief Konstruktor.
	*/
	Identyfikator();

	/**
	* \brief Konstruktor.
	*
	* Metoda ustawia warto�� atrybutu na tak� jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	explicit Identyfikator( const type_name& wartosc );

	/**
	* \brief Konstruktor.
	*
	* Metoda ustawia warto�� atrybutu na tak� jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	explicit Identyfikator( const Ilosc& wartosc );

	/**
	* \brief Konstruktor kopiuj�cy.
	*
	* Metoda ustawia warto�� atrybutu na tak� jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	Identyfikator( const Identyfikator& wartosc );

	/**
	* \brief Destruktor.
	*/
	virtual ~Identyfikator();

	/**
	* \brief Operator r�wno�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator==( const Identyfikator& wartosc )const;

	/**
	* \brief Operator nier�wno�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator!=( const Identyfikator& wartosc )const;

	/**
	* \brief Operator s�abej mniejszo�ci.
	*
	* \param[in] wartosc - Warto�� por�wnywana z atrybutem klasy.
	*/
	bool operator<( const Identyfikator& wartosc )const;

	/**
	* \brief Operator rzutowania.
	*
	* Operator u�ywany przez kontenery hasuj�ce.
	*/
	explicit operator size_t()const;

	/**
	* Funkcja s�u��ca jako podstawa do tworzenia napis�w z opisem klasy.
	* \return Napis zawieraj�cy opis klasy.
	*/
	std::string napis()const override;
};

struct IdTypeHash {
    size_t operator()(const Identyfikator& t) const {
		return static_cast<size_t>(t());
    }
};
