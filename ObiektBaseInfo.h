#pragma once
#include "Main.h"
#include "Info.h"
#include "Poziom.h"
#include "Klucz.h"

class ObiektBase;

class ObiektBaseInfo:
	public Info,
	virtual public LoggerInterface
{
public:

	ObiektBaseInfo( const Info& i , const Poziom& p ) throw();

	explicit ObiektBaseInfo( ticpp::Node* ) throw(WyjatekParseraXML);

	virtual ~ObiektBaseInfo();
	
	virtual ObiektBase* TworzEgzemplarz( const Ilosc&, const IdType& ) const;

	const Poziom& getPoziom()const;

	string toString() const;

private:
	Poziom poziom;
};

