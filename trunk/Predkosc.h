#pragma once
#include "Main.h"
#include "BaseTypes.h"

class Predkosc:
	virtual public LoggerInterface,
	public BaseInterface<SPG::Predkosc>
{
public:	
	Predkosc();
	Predkosc( const Predkosc& );
	explicit Predkosc( const type_name& );
	virtual ~Predkosc();

	bool operator==( const Predkosc& )const;
	bool operator!=( const Predkosc& )const;
	bool operator<( const Predkosc& )const;
	bool operator<=( const Predkosc& )const;
	bool operator>( const Predkosc& )const;
	bool operator>=( const Predkosc& )const;

	Predkosc& operator=( const Predkosc& );
	Predkosc& operator-=( const Predkosc& );
	Predkosc& operator+=( const Predkosc& );
	Predkosc operator-( const Predkosc& )const;
	Predkosc operator+( const Predkosc& )const;

	type_name getPredkosc() const;

	void setPredkosc( const type_name& );

	string toString() const override; 
};


