#pragma once
#include "stdafx.h"

class BASETYPES_API Tekst:
	virtual public LoggerInterface,
	public BaseInterface<SPG::Tekst>
{
private:
	type_name tekst;

	type_name dodajCudzyslow()const;
public:
	Tekst();
	Tekst( const type_name& );
	Tekst( const Tekst& );
	virtual ~Tekst();

	Tekst operator+( const Tekst& ) const;
	Tekst& operator+=( const Tekst& );
	Tekst& operator=( const Tekst& );

	bool operator==( const Tekst& ) const;
	bool operator!=( const Tekst& ) const;

	bool isEmpty() const;

	type_name getTekst()const;
	void setTekst( const type_name& );

	type_name value()const override;

	string toString()const override;
};

