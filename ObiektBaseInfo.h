#pragma once
#include "Main.h"
#include "Info.h"
#include "Poziom.h"
#include "Klucz.h"

class ObiektBazowy;
class Planeta;

class ObiektBaseInfo:
	public Info,
	virtual public LoggerInterface
{
	friend class Gra;
public:

	ObiektBaseInfo( const Info& i , const Poziom& p ) throw();

	explicit ObiektBaseInfo( TiXmlElement* ) throw(WyjatekParseraXML);
		
	virtual ObiektBazowy* TworzEgzemplarz( const Ilosc&, const Identyfikator& ) const;

	const Poziom& getPoziom()const;

	string napis() const;

private:

	virtual bool Tworz( const Gra& g, Planeta& p , const Ilosc& i ) const;

	Poziom poziom;
};

