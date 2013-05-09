#pragma once
#include "stdafx.h"

class BASETYPES_API IdType :
	virtual public LoggerInterface,
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

	bool operator<( const IdType& )const;

	operator size_t()const;
	
	type_name getId()const;
	void setId( const type_name & ID );

	type_name value()const override;

	string toString()const override;
};

