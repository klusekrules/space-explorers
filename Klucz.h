#pragma once
#include "Main.h"
#include "TypyProste.h"
#include "Poziom.h"
#include "Identyfikator.h"
#include "parser\ticpp.h"
#include "WyjatekParseraXML.h"

class Klucz:
	virtual public LoggerInterface,
	public PodstawowyInterfejs< pair < Identyfikator, Poziom > >
{
public:
	Klucz();
	Klucz( const Identyfikator& , const Poziom& );
	explicit Klucz( const type_name& );
	Klucz( const Klucz& );
	virtual ~Klucz();
	
	bool operator==( const Klucz& )const;
	bool operator!=( const Klucz& )const;
	bool operator<( const Klucz& )const;
	
	string napis()const override;
};

struct KluczHash {
    size_t operator()(const Klucz& t) const {
		size_t z = (t().first() + (t().second() << 16) ) * t().second();
		return z;
    }
};
