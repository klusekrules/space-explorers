#pragma once
#include "Main.h"
#include "IdType.h"
#include "parser\ticpp.h"
#include "WyjatekParseraXML.h"

/**
* Klasa bazowa przechowuj�ca informacje o ID klasy pochodnej.
*/
class Base:
	public LoggerInterface<Base>
{
public:	
	
	/**
	* Definicja typu klasy loguj�cej dla klasy Base.
	*/
	typedef LoggerInterface<Base> LogBase;
		
	/**
	* Konstruktor klasy Base z podan� warto�ci� ID.
	* \param id - Id przechowywane przez klase.
	*/
	explicit Base( const IdType& id );
	explicit Base( ticpp::Node* );
	
	/**
	* Destruktor domy�lny.
	*/
	virtual ~Base();

	/**
	* Metoda zwracaj�ca ID klasy
	* \return Id klasy.
	*/
	const IdType& getId()const;

	/**
	* Metoda ustawiaj�ca ID klasy
	* \param id - Nowa warto�� ID klasy.
	*/
	void setId( const IdType& id );

	/**
	* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
	* \return Napis zwieraj�cy opis klasy.
	*/
	virtual string toString() const override;
private:

	IdType id; /// Warto�� id obiektu.
};

