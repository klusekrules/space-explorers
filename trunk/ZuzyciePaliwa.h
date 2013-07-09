#pragma once
#include "Main.h"
#include "BaseTypes.h"

class ZuzyciePaliwa:
	virtual public LoggerInterface,
	public BaseInterface<SPG::ZuzyciePaliwa>
{
public:	
	ZuzyciePaliwa();
	ZuzyciePaliwa( const ZuzyciePaliwa& );
	explicit ZuzyciePaliwa( const type_name& );
	virtual ~ZuzyciePaliwa();

	bool operator==( const ZuzyciePaliwa& )const;
	bool operator!=( const ZuzyciePaliwa& )const;
	bool operator<( const ZuzyciePaliwa& )const;
	bool operator<=( const ZuzyciePaliwa& )const;
	bool operator>( const ZuzyciePaliwa& )const;
	bool operator>=( const ZuzyciePaliwa& )const;

	ZuzyciePaliwa& operator=( const ZuzyciePaliwa& );
	ZuzyciePaliwa& operator-=( const ZuzyciePaliwa& );
	ZuzyciePaliwa& operator+=( const ZuzyciePaliwa& );
	ZuzyciePaliwa operator-( const ZuzyciePaliwa& )const;
	ZuzyciePaliwa operator+( const ZuzyciePaliwa& )const;

	type_name getZuzyciePaliwa() const;

	void setZuzyciePaliwa( const type_name& );

	string toString() const override; 
};


