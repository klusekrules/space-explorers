#pragma once
#include "Main.h"
#include "TypyProste.h"

class ZuzyciePaliwa:
	virtual public LoggerInterface,
	public PodstawowyInterfejs<SPG::ZuzyciePaliwa>
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
	
	string napis() const override; 
};


