#pragma once
#include "Main.h"
#include "BaseTypes.h"

class Ilosc:	
	public LoggerInterface<Ilosc>,
	public BaseInterface<SPG::IloscJednostek>
{
private:
	type_name ilosc;
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

	Ilosc operator*( const Ilosc& )const;

	type_name getIlosc()const;

	void setIlosc( const type_name& );

	type_name value() const override;

	string toString() const override;
};
