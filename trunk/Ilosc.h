#pragma once
#include "Main.h"
#include "TypyProste.h"

class Ilosc:	
	virtual public LoggerInterface,
	public PodstawowyInterfejs<SPG::IloscJednostek>
{
public:
	Ilosc();
	explicit Ilosc( const type_name& );
	Ilosc( const Ilosc& );
	virtual ~Ilosc();

	bool operator<( const Ilosc& ) const;
	bool operator>( const Ilosc& ) const;
	bool operator==( const Ilosc& ) const;
	bool operator!=( const Ilosc& ) const;
	bool operator<=( const Ilosc& ) const;
	bool operator>=( const Ilosc& ) const;

	Ilosc operator+( const Ilosc& ) const;
	Ilosc operator-( const Ilosc& ) const;
	Ilosc& operator+=( const Ilosc& );
	Ilosc& operator-=( const Ilosc& );
	Ilosc& operator=( const Ilosc& );

	Ilosc& operator++( );
	Ilosc operator++( int );

	Ilosc operator*( const Ilosc& )const;

	string napis() const override;
};
