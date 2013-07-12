#pragma once
#include "Main.h"
#include "Identyfikator.h"
#include "Serializacja.h"
#include "parser\ticpp.h"
#include "WyjatekParseraXML.h"

/**
* Klasa bazowa przechowuj¹ca informacje o ID klasy pochodnej.
*/
class Base:
	virtual public LoggerInterface,
	virtual public Serializacja
{
public:	
			
	/**
	* Konstruktor klasy Base z podan¹ wartoœci¹ ID.
	* \param id - Id przechowywane przez klase.
	*/
	explicit Base( const Identyfikator& id ) throw();
	explicit Base( TiXmlElement * ) throw(WyjatekParseraXML);
	
	/**
	* Destruktor domyœlny.
	*/
	virtual ~Base();

	/**
	* Metoda zwracaj¹ca ID klasy
	* \return Id klasy.
	*/
	const Identyfikator& getId()const;

	/**
	* Metoda ustawiaj¹ca ID klasy
	* \param id - Nowa wartoœæ ID klasy.
	*/
	void setId( const Identyfikator& id );

	bool zapisz( TiXmlElement* e ) const override;

	bool odczytaj( TiXmlElement* e ) override;

	/**
	* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
	* \return Napis zwieraj¹cy opis klasy.
	*/
	string napis() const override;
private:

	Identyfikator id; /// Wartoœæ id obiektu.
};

