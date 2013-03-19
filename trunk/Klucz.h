#pragma once
#include "Main.h"
#include "BaseTypes.h"
#include "Poziom.h"
#include "IdType.h"
#include "parser\ticpp.h"
#include "WyjatekParseraXML.h"

class Klucz:
	public LoggerInterface<Klucz>,
	public BaseInterface< pair < IdType, Poziom > >
{
	type_name values;
public:
	Klucz();
	Klucz( ticpp::Node* );
	Klucz( const IdType& , const Poziom& );
	explicit Klucz( const type_name& );
	Klucz( const Klucz& );
	virtual ~Klucz();

	operator size_t() const
	{
		size_t z = (values.first.value() + (values.second.value() << 16) ) * values.second.value();
		return z; 
	}

	bool operator==( const Klucz& )const;
	bool operator!=( const Klucz& )const;

	type_name getKlucz()const;
	void setKlucz( const type_name& );

	type_name value()const override;

	string toString()const override;
};

