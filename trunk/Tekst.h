#pragma once
#include "Main.h"
#include "TypyProste.h"

class Tekst:
	virtual public LoggerInterface,
	public PodstawowyInterfejs<SPG::Tekst>
{
private:
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

	string napis()const override;
};

