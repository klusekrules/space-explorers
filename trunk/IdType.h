#pragma once
#include "Main.h"
#include "BaseTypes.h"
#include "parser\ticpp.h"
#include "Ilosc.h"

class IdType :
	virtual public LoggerInterface,
	public BaseInterface<SPG::IdType>
{
public:
	
	IdType();
	explicit IdType( TiXmlElement* );
	explicit IdType( const type_name& ID );
	explicit IdType( const Ilosc& ID );
	IdType( const IdType& a );
	virtual ~IdType();

	bool operator==( const IdType& )const;
	bool operator!=( const IdType& )const;

	bool operator<( const IdType& )const;

	explicit operator size_t()const;
	
	type_name getId()const;
	void setId( const type_name & ID );

	string toString()const override;
};

struct IdTypeHash {
    size_t operator()(const IdType& t) const {
		return static_cast<size_t>(t());
    }
};
