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
	type_name values;
	friend struct KluczHash;
public:
	Klucz();
	Klucz( ticpp::Node* );
	Klucz( const IdType& , const Poziom& );
	explicit Klucz( const type_name& );
	Klucz( const Klucz& );
	virtual ~Klucz();
	
	bool operator==( const Klucz& )const;
	bool operator!=( const Klucz& )const;

	type_name getKlucz()const;
	void setKlucz( const type_name& );

	type_name value()const override;

	string toString()const override;
};

struct KluczHash {
    size_t operator()(const Klucz& t){
		size_t z = (t.values.first.value() + (t.values.second.value() << 16) ) * t.values.second.value();
		return z;
    }
};
