#pragma once
#include "Main.h"
#include "IdType.h"
#include "parser\ticpp.h"
#include "WyjatekParseraXML.h"

/**
* Klasa bazowa przechowuj¹ca informacje o ID klasy pochodnej.
*/
class Base:
	public LoggerInterface<Base>
{
public:	
	
	/**
	* Definicja typu klasy loguj¹cej dla klasy Base.
	*/
	typedef LoggerInterface<Base> LogBase;
		
	/**
	* Konstruktor klasy Base z podan¹ wartoœci¹ ID.
	* \param id - Id przechowywane przez klase.
	*/
	explicit Base( const IdType& id );
	explicit Base( ticpp::Node* );
	
	/**
	* Destruktor domyœlny.
	*/
	virtual ~Base();

	/**
	* Metoda zwracaj¹ca ID klasy
	* \return Id klasy.
	*/
	const IdType& getId()const;

	/**
	* Metoda ustawiaj¹ca ID klasy
	* \param id - Nowa wartoœæ ID klasy.
	*/
	void setId( const IdType& id );

	/**
	* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
	* \return Napis zwieraj¹cy opis klasy.
	*/
	virtual string toString() const override;
private:

	IdType id; /// Wartoœæ id obiektu.
};

