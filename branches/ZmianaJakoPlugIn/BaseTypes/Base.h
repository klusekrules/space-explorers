#pragma once
#include "stdafx.h"
#include "IdType.h"
#include "..\parser\ticpp.h"
#include "WyjatekParseraXML.h"

/**
* Klasa bazowa przechowuj¹ca informacje o ID klasy pochodnej.
*/
class BASETYPES_API Base:
	virtual public LoggerInterface
{
public:	
			
	/**
	* Konstruktor klasy Base z podan¹ wartoœci¹ ID.
	* \param id - Id przechowywane przez klase.
	*/
	explicit Base( const IdType& id ) throw();
	explicit Base( ticpp::Node* ) throw(WyjatekParseraXML);
	
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
	string toString() const override;
private:

	IdType id; /// Wartoœæ id obiektu.
};

