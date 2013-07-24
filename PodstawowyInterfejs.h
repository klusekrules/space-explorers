#pragma once
#pragma warning( disable : 4290 )
/**
* \brief Klasa bazowa dla podstawowych typów atrybutów.
*
* Klasa bazowa z uniwersalnym interfejsem dla u³atwienia zmiany typów podstawowych w grze
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
	* Metoda ustawia wartoœæ atrybutu na tak¹ jak jest podana w parametrze konstruktora.
	* \param[in] wartosc - Wartoœæ na jak¹ ma byæ ustawiony atrybut klasy.
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
	* Metoda pobieraj¹ca wartoœæ atrybutu.
	* \return Wartoœæ atrybutu.
	*/
	type_name operator()() const {
		return wartosc_;
	}

	/**
	* Metoda ustawiaj¹ca wartoœc atrybutu.
	* \param[in] wartosc - Nowa wartoœæ atrybutu.
	*/
	void operator()( const type_name& wartosc ){
		wartosc_ = wartosc;
	}

protected:
	type_name wartosc_; /// Przechowywana wartoœæ.
};

