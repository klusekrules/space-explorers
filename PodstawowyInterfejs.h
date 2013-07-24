#pragma once
#pragma warning( disable : 4290 )
/**
* \brief Klasa bazowa dla podstawowych typ�w atrybut�w.
*
* Klasa bazowa z uniwersalnym interfejsem dla u�atwienia zmiany typ�w podstawowych w grze
* oraz dla ujednolicenia interfejsu.
* \author Daniel Wojdak
* \version 1
* \date 10-07-2013
*/
template < typename T >
 class PodstawowyInterfejs
{
public:

	/**
	* Typ przechowywanych danych.
	*/
	typedef T type_name;


	/**
	* \brief Konstruktor.
	*
	* Metoda ustawia warto�� atrybutu na tak� jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Warto�� na jak� ma by� ustawiony atrybut klasy.
	*/
	PodstawowyInterfejs( const type_name& wartosc )
		: wartosc_ ( wartosc )
	{
	}

	/**
	* Destruktor.
	*/
	virtual ~PodstawowyInterfejs(){
	}

	/**
	* Metoda pobieraj�ca warto�� atrybutu.
	* \return Warto�� atrybutu.
	*/
	type_name operator()() const {
		return wartosc_;
	}

	/**
	* Metoda ustawiaj�ca warto�c atrybutu.
	* \param[in] wartosc - Nowa warto�� atrybutu.
	*/
	void operator()( const type_name& wartosc ){
		wartosc_ = wartosc;
	}

protected:
	type_name wartosc_; /// Przechowywana warto��.
};

