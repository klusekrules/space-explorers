#pragma once
#include "stdafx.h"

class BASETYPES_API MocSilnika:
	virtual public LoggerInterface,
	public BaseInterface<SPG::MocSilnika>
{
private:
	type_name mocSilnika;
public:	
	MocSilnika();
	MocSilnika( const MocSilnika& );
	explicit MocSilnika( const type_name& );
	virtual ~MocSilnika();

	bool operator==( const MocSilnika& )const;
	bool operator!=( const MocSilnika& )const;
	bool operator<( const MocSilnika& )const;
	bool operator<=( const MocSilnika& )const;
	bool operator>( const MocSilnika& )const;
	bool operator>=( const MocSilnika& )const;

	MocSilnika& operator=( const MocSilnika& );
	MocSilnika& operator-=( const MocSilnika& );
	MocSilnika& operator+=( const MocSilnika& );
	MocSilnika operator-( const MocSilnika& )const;
	MocSilnika operator+( const MocSilnika& )const;

	type_name getMocSilnika() const;

	void setMocSilnika( const type_name& );

	type_name value() const override;

	string toString() const override; 
};


