#pragma once
#include "Main.h"
#include "BaseTypes.h"
#include "Fluktuacja.h"
#include "Ilosc.h"

class Masa:
	virtual public LoggerInterface,
	public BaseInterface<SPG::Masa>
{
public:
	Masa();
	Masa( const Masa& );
	explicit Masa( const type_name& );
	virtual ~Masa();

	bool operator==( const Masa& )const;
	bool operator!=( const Masa& )const;
	bool operator<( const Masa& )const;
	bool operator<=( const Masa& )const;
	bool operator>( const Masa& )const;
	bool operator>=( const Masa& )const;

	Masa& operator=( const Masa& );
	Masa& operator-=( const Masa& );
	Masa& operator+=( const Masa& );
	Masa operator-( const Masa& )const;
	Masa operator+( const Masa& )const;
	Masa operator*( const Fluktuacja& )const;
	Masa& operator*=( const Fluktuacja& );
	Masa operator*( const Ilosc& )const;
	Masa& operator*=( const Ilosc& );
	
	string toString() const override; 
};