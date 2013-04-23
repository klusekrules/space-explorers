#pragma once
#include "Main.h"
#include "Info.h"
#include "Poziom.h"
#include "Klucz.h"

class ObiektBase;

class ObiektBaseInfo:
	public Info,
	public LoggerInterface<ObiektBaseInfo>
{
public:
	typedef LoggerInterface<ObiektBaseInfo> LogObiektBaseInfo;

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

