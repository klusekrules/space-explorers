#pragma once
#include "BaseTypes.h"

class Dystans:
	virtual public LoggerInterface,
	public BaseInterface<SPG::Dystans>
{
private:
	type_name dystans;
public:	
	Dystans();
	Dystans( const Dystans& );
	explicit Dystans( const type_name& );
	virtual ~Dystans();

	bool operator==( const Dystans& )const;
	bool operator!=( const Dystans& )const;
	bool operator<( const Dystans& )const;
	bool operator<=( const Dystans& )const;
	bool operator>( const Dystans& )const;
	bool operator>=( const Dystans& )const;

	Dystans& operator=( const Dystans& );
	Dystans& operator-=( const Dystans& );
	Dystans& operator+=( const Dystans& );
	Dystans operator-( const Dystans& )const;
	Dystans operator+( const Dystans& )const;

	type_name getDystans() const;

	void setDystans( const type_name& );

	type_name value() const override;

	string toString() const override; 
};

