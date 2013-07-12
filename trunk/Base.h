#pragma once
#include "Main.h"
#include "Identyfikator.h"
#include "Serializacja.h"
#include "parser\ticpp.h"
#include "WyjatekParseraXML.h"

/**
* Klasa bazowa przechowuj�ca informacje o ID klasy pochodnej.
*/
class Base:
	virtual public LoggerInterface,
	virtual public Serializacja
{
public:	
			
	/**
	* Konstruktor klasy Base z podan� warto�ci� ID.
	* \param id - Id przechowywane przez klase.
	*/
	explicit Base( const Identyfikator& id ) throw();
	explicit Base( TiXmlElement * ) throw(WyjatekParseraXML);
	
	/**
	* Destruktor domy�lny.
	*/
	virtual ~Base();

	/**
	* Metoda zwracaj�ca ID klasy
	* \return Id klasy.
	*/
	const Identyfikator& getId()const;

	/**
	* Metoda ustawiaj�ca ID klasy
	* \param id - Nowa warto�� ID klasy.
	*/
	void setId( const Identyfikator& id );

	bool zapisz( TiXmlElement* e ) const override;

	bool odczytaj( TiXmlElement* e ) override;

	/**
	* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
	* \return Napis zwieraj�cy opis klasy.
	*/
	string napis() const override;
private:

	Identyfikator id; /// Warto�� id obiektu.
};

