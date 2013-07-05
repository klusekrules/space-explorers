#pragma once
#include "Main.h"
#include "Info.h"
#include "Poziom.h"
#include "Klucz.h"

class ObiektBase;
class Planeta;

class ObiektBaseInfo:
	public Info,
	virtual public LoggerInterface
{
	friend class Gra;
public:

	ObiektBaseInfo( const Info& i , const Poziom& p ) throw();

	explicit ObiektBaseInfo( ticpp::Node* ) throw(WyjatekParseraXML);
		
	virtual ObiektBase* TworzEgzemplarz( const Ilosc&, const IdType& ) const;

	const Poziom& getPoziom()const;

	string toString() const;

private:

	virtual bool Tworz( const Gra& g, Planeta& p , const Ilosc& i ) const;

	Poziom poziom;
};

