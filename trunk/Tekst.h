#pragma once
#include "Main.h"
#include "BaseTypes.h"

class Tekst:
	public LoggerInterface<Tekst>,
	public BaseInterface<SPG::Tekst>
{
private:
	type_name tekst;
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

