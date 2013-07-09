#pragma once
#include "Main.h"
#include "BaseTypes.h"

class MocSilnika:
	virtual public LoggerInterface,
	public BaseInterface<SPG::MocSilnika>
{
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

	string toString() const override; 
};


