#pragma once
#include "Main.h"
#include "TypyProste.h"

class Poziom:	
	virtual public LoggerInterface,
	public PodstawowyInterfejs<SPG::Poziom>
{
public:
	Poziom();
	explicit Poziom( const type_name& );
	Poziom( const Poziom& );
	virtual ~Poziom();

	bool operator==( const Poziom& )const;
	bool operator!=( const Poziom& )const;
	bool operator<( const Poziom& )const;
	bool operator<=( const Poziom& )const;
	bool operator>( const Poziom& )const;
	bool operator>=( const Poziom& )const;

	Poziom& operator=( const Poziom& );
	Poziom& operator-=( const Poziom& );
	Poziom& operator+=( const Poziom& );
	Poziom operator-( const Poziom& )const;
	Poziom operator+( const Poziom& )const;

	Poziom& operator++( );
	Poziom operator++( int );

	explicit operator size_t () const;
	
	string napis() const override;
};

