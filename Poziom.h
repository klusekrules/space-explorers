#pragma once
#include "Main.h"
#include "BaseTypes.h"

class Poziom:	
	virtual public LoggerInterface,
	public BaseInterface<SPG::Poziom>
{
private:
	type_name pPoziom;
public:
	Poziom();
	explicit Poziom( const type_name& );
	Poziom( const Poziom& );
	virtual ~Poziom();

	bool operator==( const Poziom& )const;
	bool operator!=( const Poziom& )const;
	bool operator<( const Poziom& )const;
	bool operator<=( const Poziom& )const;
	bool operator>( const Poziom& )const;
	bool operator>=( const Poziom& )const;

	Poziom& operator=( const Poziom& );
	Poziom& operator-=( const Poziom& );
	Poziom& operator+=( const Poziom& );
	Poziom operator-( const Poziom& )const;
	Poziom operator+( const Poziom& )const;

	Poziom& operator++( );
	Poziom operator++( int );

	operator size_t () const;

	type_name getPoziom()const;

	void setPoziom( const type_name& );

	type_name value() const override;

	string toString() const override;
};

