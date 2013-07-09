#pragma once
#include "Main.h"
#include "BaseTypes.h"

class Bool:
	virtual public LoggerInterface,
	public BaseInterface<bool>
{
public:	
	Bool();
	Bool( const Bool& );
	explicit Bool( const type_name& );
	virtual ~Bool();
	
	bool operator==( const Bool& )const;
	bool operator!=( const Bool& )const;

	Bool& operator=( const Bool& );
	Bool& operator=( const type_name& b );
	
	string toString() const override; 
};

