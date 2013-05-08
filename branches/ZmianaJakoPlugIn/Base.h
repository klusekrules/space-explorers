#pragma once
#include "Main.h"
#include "BaseTypes\IdType.h"
#include "parser\ticpp.h"
#include "BaseTypes\WyjatekParseraXML.h"

/**
* Klasa bazowa przechowuj�ca informacje o ID klasy pochodnej.
*/
class Base:
	virtual public LoggerInterface
{
public:	
			
	/**
	* Konstruktor klasy Base z podan� warto�ci� ID.
	* \param id - Id przechowywane przez klase.
	*/
	explicit Base( const IdType& id ) throw();
	explicit Base( ticpp::Node* ) throw(WyjatekParseraXML);
	
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
	string toString() const override;
private:

	IdType id; /// Warto�� id obiektu.
};

