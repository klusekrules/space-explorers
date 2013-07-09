#pragma once
#include "Main.h"
#include "BaseTypes.h"
#include "Fluktuacja.h"
#include "Ilosc.h"

class Powierzchnia:	
	virtual public LoggerInterface,
	public BaseInterface<SPG::Powierzchnia>
{
public:
	Powierzchnia();
	Powierzchnia( const Powierzchnia& );
	explicit Powierzchnia( const type_name& );
	virtual ~Powierzchnia();

	bool operator==( const Powierzchnia& )const;
	bool operator!=( const Powierzchnia& )const;
	bool operator<( const Powierzchnia& )const;
	bool operator<=( const Powierzchnia& )const;
	bool operator>( const Powierzchnia& )const;
	bool operator>=( const Powierzchnia& )const;

	Powierzchnia& operator=( const Powierzchnia& );
	Powierzchnia& operator-=( const Powierzchnia& );
	Powierzchnia& operator+=( const Powierzchnia& );
	Powierzchnia operator-( const Powierzchnia& )const;
	Powierzchnia operator+( const Powierzchnia& )const;
	Powierzchnia operator*( const Fluktuacja& )const;
	Powierzchnia& operator*=( const Fluktuacja& );
	Powierzchnia operator*( const Ilosc& )const;
	Powierzchnia& operator*=( const Ilosc& );
	
	string toString() const override; 
};

