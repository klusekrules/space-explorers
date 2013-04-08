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

	ObiektBaseInfo( const Info& i , const Poziom& p );

	explicit ObiektBaseInfo( ticpp::Node* );

	virtual ~ObiektBaseInfo();
	
	virtual ObiektBase* TworzEgzemplarz( const Ilosc& ) const;

	/**
	* Metoda s³u¿y do zwrócenia klucza jednozancznie identyfikuj¹cego typ obiektu. 
	* Klucz sk³ada siê z id obiektu i poziomu obiektu.
	* \return Klucz identyfikuj¹cy obiekt.
	*/
	Klucz ID() const;

	const Poziom& getPoziom()const;

	string toString() const;

private:
	Poziom poziom;
};

