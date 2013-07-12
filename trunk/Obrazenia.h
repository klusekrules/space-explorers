#pragma once
#include "Main.h"
#include "TypyProste.h"

class Obrazenia:
	virtual public LoggerInterface,
	public PodstawowyInterfejs<SPG::Obrazenia>
{
public:	
	Obrazenia();
	Obrazenia( const Obrazenia& );
	explicit Obrazenia( const type_name& );
	virtual ~Obrazenia();

	bool operator==( const Obrazenia& )const;
	bool operator!=( const Obrazenia& )const;
	bool operator<( const Obrazenia& )const;
	bool operator<=( const Obrazenia& )const;
	bool operator>( const Obrazenia& )const;
	bool operator>=( const Obrazenia& )const;

	Obrazenia& operator=( const Obrazenia& );
	Obrazenia& operator-=( const Obrazenia& );
	Obrazenia& operator+=( const Obrazenia& );
	Obrazenia operator-( const Obrazenia& )const;
	Obrazenia operator+( const Obrazenia& )const;
	
	string napis() const override; 
};