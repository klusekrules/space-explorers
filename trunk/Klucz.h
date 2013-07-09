#pragma once
#include "Main.h"
#include "BaseTypes.h"
#include "Poziom.h"
#include "IdType.h"
#include "parser\ticpp.h"
#include "WyjatekParseraXML.h"

class Klucz:
	virtual public LoggerInterface,
	public BaseInterface< pair < IdType, Poziom > >
{
public:
	Klucz();
	explicit Klucz( TiXmlElement* );
	Klucz( const IdType& , const Poziom& );
	explicit Klucz( const type_name& );
	Klucz( const Klucz& );
	virtual ~Klucz();
	
	bool operator==( const Klucz& )const;
	bool operator!=( const Klucz& )const;
	bool operator<( const Klucz& )const;

	type_name getKlucz()const;
	void setKlucz( const type_name& );

	string toString()const override;
};

struct KluczHash {
    size_t operator()(const Klucz& t) const {
		size_t z = (t().first() + (t().second() << 16) ) * t().second();
		return z;
    }
};
