#pragma once
#include "Main.h"
#include "BaseTypes.h"

class IdType :
	public LoggerInterface<IdType>,
	public BaseInterface<SPG::IdType>
{
protected:
	type_name id;
public:
	IdType();
	explicit IdType( const type_name& ID );
	IdType( const IdType& a );
	virtual ~IdType();

	bool operator==( const IdType& )const;
	bool operator!=( const IdType& )const;
	
	type_name getId()const;
	void setId( const type_name & ID );

	type_name value()const override;

	string toString()const override;
};

