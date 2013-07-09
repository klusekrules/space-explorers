#pragma once
#include "Main.h"
#include "BaseTypes.h"

class Obrazenia:
	virtual public LoggerInterface,
	public BaseInterface<SPG::Obrazenia>
{
public:	
	Obrazenia();
	Obrazenia( const Obrazenia& );
	explicit Obrazenia( const type_name& );
	virtual ~Obrazenia();

	bool operator==( const Obrazenia& )const;
	bool operator!=( const Obrazenia& )const;
	bool operator<( const Obrazenia& )const;
	bool operator<=( const Obrazenia& )const;
	bool operator>( const Obrazenia& )const;
	bool operator>=( const Obrazenia& )const;

	Obrazenia& operator=( const Obrazenia& );
	Obrazenia& operator-=( const Obrazenia& );
	Obrazenia& operator+=( const Obrazenia& );
	Obrazenia operator-( const Obrazenia& )const;
	Obrazenia operator+( const Obrazenia& )const;

	type_name getObrazenia() const;

	void setObrazenia( const type_name& );

	string toString() const override; 
};