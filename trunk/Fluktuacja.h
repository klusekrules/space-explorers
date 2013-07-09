#pragma once
#include "Main.h"
#include "BaseTypes.h"

class Fluktuacja:
	virtual public LoggerInterface,
	public BaseInterface<SPG::Fluktuacja>
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
	
	string toString() const override; 
};

