#pragma once
#include "Logger\LoggerInterface.h"
#include "TypyProste.h"
#include "Ilosc.h"
/**
* \brief Klas przechowujaca identyfikator.
*
* Klasa reprezentuj¹ca identyfikator.
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
	* Metoda ustawia wartoœæ atrybutu na tak¹ jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Wartoœæ na jak¹ ma byæ ustawiony atrybut klasy.
	*/
	explicit Identyfikator( const type_name& wartosc );

	/**
	* \brief Konstruktor.
	*
	* Metoda ustawia wartoœæ atrybutu na tak¹ jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Wartoœæ na jak¹ ma byæ ustawiony atrybut klasy.
	*/
	explicit Identyfikator( const Ilosc& wartosc );

	/**
	* \brief Konstruktor kopiuj¹cy.
	*
	* Metoda ustawia wartoœæ atrybutu na tak¹ jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Wartoœæ na jak¹ ma byæ ustawiony atrybut klasy.
	*/
	Identyfikator( const Identyfikator& wartosc );

	/**
	* \brief Destruktor.
	*/
	virtual ~Identyfikator();

	/**
	* \brief Operator równoœci.
	*
	* \param[in] wartosc - Wartoœæ porównywana z atrybutem klasy.
	*/
	bool operator==( const Identyfikator& wartosc )const;

	/**
	* \brief Operator nierównoœci.
	*
	* \param[in] wartosc - Wartoœæ porównywana z atrybutem klasy.
	*/
	bool operator!=( const Identyfikator& wartosc )const;

	/**
	* \brief Operator s³abej mniejszoœci.
	*
	* \param[in] wartosc - Wartoœæ porównywana z atrybutem klasy.
	*/
	bool operator<( const Identyfikator& wartosc )const;

	/**
	* \brief Operator rzutowania.
	*
	* Operator u¿ywany przez kontenery hasuj¹ce.
	*/
	explicit operator size_t()const;

	/**
	* Funkcja s³u¿¹ca jako podstawa do tworzenia napisów z opisem klasy.
	* \return Napis zawieraj¹cy opis klasy.
	*/
	std::string napis()const override;
};

struct IdTypeHash {
    size_t operator()(const Identyfikator& t) const {
		return static_cast<size_t>(t());
    }
};
