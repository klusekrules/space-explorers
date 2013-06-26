#pragma once
#include "Main.h"
#include "BaseTypes.h"
#include "parser\ticpp.h"

class IdType :
	virtual public LoggerInterface,
	public BaseInterface<SPG::IdType>
{
protected:
	type_name id;
public:
	
	IdType();
	IdType( ticpp::Node* );
	explicit IdType( const type_name& ID );
	IdType( const IdType& a );
	virtual ~IdType();

	bool operator==( const IdType& )const;
	bool operator!=( const IdType& )const;

	bool operator<( const IdType& )const;

	operator size_t()const;
	
	type_name getId()const;
	void setId( const type_name & ID );

	type_name value()const override;

	string toString()const override;
};

struct IdTypeHash {
    size_t operator()(const IdType& t) const {
		return static_cast<size_t>(t.value());
    }
};
