#pragma once
#include "Main.h"
#include "Info.h"
#include "BaseTypes\BaseTypes.h"
#include "BaseTypes\Wyjatki.h"

class ObiektBase;

class ObiektBaseInfo:
	public Info,
	virtual public LoggerInterface
{
public:

	ObiektBaseInfo( const Info& i , const Poziom& p ) throw();

	explicit ObiektBaseInfo( ticpp::Node* ) throw(WyjatekParseraXML);

	virtual ~ObiektBaseInfo();
	
	virtual ObiektBase* TworzEgzemplarz( const Ilosc& ) const;

	/**
	* Metoda s�u�y do zwr�cenia klucza jednozancznie identyfikuj�cego typ obiektu. 
	* Klucz sk�ada si� z id obiektu i poziomu obiektu.
	* \return Klucz identyfikuj�cy obiekt.
	*/
	Klucz ID() const;

	const Poziom& getPoziom()const;

	string toString() const;

private:
	Poziom poziom;
};

