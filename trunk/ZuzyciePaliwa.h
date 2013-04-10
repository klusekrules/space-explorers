#pragma once
#include "Main.h"
#include "BaseTypes.h"

class ZuzyciePaliwa:
	public LoggerInterface<ZuzyciePaliwa>,
	public BaseInterface<SPG::ZuzyciePaliwa>
{
private:
	type_name zuzyciePaliwa;
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

	type_name value() const override;

	string toString() const override; 
};

