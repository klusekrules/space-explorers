#pragma once
#include "Main.h"
#include "TypyProste.h"

class Fluktuacja:
	virtual public LoggerInterface,
	public PodstawowyInterfejs<SPG::Fluktuacja>
{
public:
	Fluktuacja();
	Fluktuacja( const Fluktuacja& );
	explicit Fluktuacja( const type_name& );
	virtual ~Fluktuacja();

	bool operator==( const Fluktuacja& )const;
	bool operator!=( const Fluktuacja& )const;
	bool operator<( const Fluktuacja& )const;
	bool operator>( const Fluktuacja& )const;
	bool operator<=( const Fluktuacja& )const;
	bool operator>=( const Fluktuacja& )const;

	Fluktuacja& operator=( const Fluktuacja& );
	Fluktuacja& operator-=( const Fluktuacja& );
	Fluktuacja& operator+=( const Fluktuacja& );
	Fluktuacja operator-( const Fluktuacja& )const;
	Fluktuacja operator+( const Fluktuacja& )const;
	
	string napis() const override; 
};

