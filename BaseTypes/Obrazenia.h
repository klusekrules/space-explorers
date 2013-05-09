#pragma once
#include "stdafx.h"

class BASETYPES_API Obrazenia:
	virtual public LoggerInterface,
	public BaseInterface<SPG::Obrazenia>
{
private:
	type_name obrazenia;
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

	type_name value() const override;

	string toString() const override; 
};