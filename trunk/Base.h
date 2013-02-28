#pragma once
#include "Main.h"
#include "IdType.h"

/**
* Klasa bazowa przechowuj�ca informacje o ID klasy pochodnej.
*/
class Base:
	public IdType,
	public LoggerInterface<Base>
{
public:	
	
	/**
	* Definicja typu klasy loguj�cej dla klasy Base.
	*/
	typedef LoggerInterface<Base> LogBase;

	/**
	* Konstruktor domy�lny.
	*/
	explicit Base();
	
	/**
	* Konstruktor klasy Base z podan� warto�ci� ID.
	* \param id - Id przechowywane przez klase.
	*/
	explicit Base( const IdType& id);
	
	/**
	* Destruktor domy�lny.
	*/
	virtual ~Base();

	/**
	* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
	* \return Napis zwieraj�cy opis klasy.
	*/
	virtual string toString() const override;
};

