#pragma once
#include "Main.h"
#include "BaseTypes.h"

class Dystans:
	virtual public LoggerInterface,
	public BaseInterface<SPG::Dystans>
{
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
	
	string napis() const override; 
};

