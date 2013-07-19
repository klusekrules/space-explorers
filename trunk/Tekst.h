#pragma once
#include "Logger\LoggerInterface.h"
#include "TypyProste.h"

/**
* \brief Klas przechowujaca tekst.
*
* Klasa reprezentuj¹ca tekst.
* \author Daniel Wojdak
* \version 1
* \date 19-07-2013
*/
class Tekst:
	virtual public LoggerInterface,
	public PodstawowyInterfejs<SPG::Tekst>
{
private:

	/**
	* \brief Metoda pomocnicza
	*
	* Metoda skleja cudzys³ów z napisem i zwraca otrzymany napis. Metoda nie modyfikuje atrybutru.
	* \return Napis otoczony cudzys³owem.
	*/
	type_name dodajCudzyslow() const;

public:

	/**
	* \brief Konstruktor.
	*/
	Tekst();

	/**
	* \brief Konstruktor.
	*
	* Metoda ustawia wartoœæ atrybutu na tak¹ jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Wartoœæ na jak¹ ma byæ ustawiony atrybut klasy.
	*/
	Tekst( const type_name& wartosc );

	/**
	* \brief Konstruktor kopiuj¹cy.
	*
	* Metoda ustawia wartoœæ atrybutu na tak¹ jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Wartoœæ na jak¹ ma byæ ustawiony atrybut klasy.
	*/
	Tekst( const Tekst& wartosc );

	/**
	* \brief Destruktor.
	*/
	virtual ~Tekst();

	/**
	* \brief Operator sumy.
	*
	* \param[in] wartosc - Napis jaki ma byæ dodany do atrybut klasy.
	*/
	Tekst operator+( const Tekst& wartosc ) const;

	/**
	* \brief Operator przypisania i sumy.
	*
	* \param[in] wartosc - Napis jaki ma byæ dodany do atrybut klasy.
	*/
	Tekst& operator+=( const Tekst& wartosc );

	/**
	* \brief Operator przypisania.
	*
	* \param[in] wartosc - Wartoœæ na jak¹ ma byæ ustawiony atrybut klasy.
	*/
	Tekst& operator=( const Tekst& wartosc );

	/**
	* \brief Operator równoœci.
	*
	* \param[in] wartosc - Wartoœæ porównywana z atrybutem klasy.
	*/
	bool operator==( const Tekst& wartosc ) const;

	/**
	* \brief Operator nierównoœci.
	*
	* \param[in] wartosc - Wartoœæ porównywana z atrybutem klasy.
	*/
	bool operator!=( const Tekst& wartosc ) const;

	/**
	* Metoda sprawdza czy napis jest pusty.
	* \return Wartoœæ true je¿eli napis jest pusty, false w przeciwnym wypadku.
	*/
	bool isEmpty() const;

	/**
	* Funkcja s³u¿¹ca jako podstawa do tworzenia napisów z opisem klasy.
	* \return Napis zawieraj¹cy opis klasy.
	*/
	string napis()const override;
};
