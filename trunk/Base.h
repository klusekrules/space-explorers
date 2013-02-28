#pragma once
#include "Main.h"
#include "IdType.h"

/**
* Klasa bazowa przechowuj¹ca informacje o ID klasy pochodnej.
*/
class Base:
	public IdType,
	public LoggerInterface<Base>
{
public:	
	
	/**
	* Definicja typu klasy loguj¹cej dla klasy Base.
	*/
	typedef LoggerInterface<Base> LogBase;

	/**
	* Konstruktor domyœlny.
	*/
	explicit Base();
	
	/**
	* Konstruktor klasy Base z podan¹ wartoœci¹ ID.
	* \param id - Id przechowywane przez klase.
	*/
	explicit Base( const IdType& id);
	
	/**
	* Destruktor domyœlny.
	*/
	virtual ~Base();

	/**
	* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
	* \return Napis zwieraj¹cy opis klasy.
	*/
	virtual string toString() const override;
};

