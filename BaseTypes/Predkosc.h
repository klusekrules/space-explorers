#pragma once
#include "stdafx.h"

class BASETYPES_API Predkosc:
	virtual public LoggerInterface,
	public BaseInterface<SPG::Predkosc>
{
private:
	type_name predkosc;
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

	type_name value() const override;

	string toString() const override; 
};


