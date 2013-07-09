#pragma once
#include "Main.h"
#include "BaseTypes.h"

class Ilosc:	
	virtual public LoggerInterface,
	public BaseInterface<SPG::IloscJednostek>
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

	type_name getIlosc()const;

	void setIlosc( const type_name& );

	string toString() const override;
};
