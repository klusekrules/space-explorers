#pragma once
#include "Main.h"
#include "TypyProste.h"
#include "Fluktuacja.h"
#include "Ilosc.h"

class Objetosc:
	virtual public LoggerInterface,
	public PodstawowyInterfejs<SPG::Objetosc>
{
public:
	Objetosc();
	Objetosc( const Objetosc& );
	explicit Objetosc( const type_name& );
	virtual ~Objetosc();

	bool operator==( const Objetosc& )const;
	bool operator!=( const Objetosc& )const;
	bool operator<( const Objetosc& )const;
	bool operator<=( const Objetosc& )const;
	bool operator>( const Objetosc& )const;
	bool operator>=( const Objetosc& )const;

	Objetosc& operator=( const Objetosc& );
	Objetosc& operator-=( const Objetosc& );
	Objetosc& operator+=( const Objetosc& );
	Objetosc operator-( const Objetosc& )const;
	Objetosc operator/( const Ilosc& )const;
	Fluktuacja operator/( const Objetosc& )const;
	Objetosc operator+( const Objetosc& )const;
	Objetosc operator*( const Fluktuacja& )const;
	Objetosc& operator*=( const Fluktuacja& );
	Objetosc operator*( const Ilosc& )const;
	Objetosc& operator*=( const Ilosc& );
	
	string napis() const override; 
};