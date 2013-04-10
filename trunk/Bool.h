#pragma once
#include "Main.h"
#include "BaseTypes.h"

class Bool:
	public LoggerInterface<Bool>,
	public BaseInterface<bool>
{
private:
	type_name bBool;
public:	
	Bool();
	Bool( const Bool& );
	explicit Bool( const type_name& );
	virtual ~Bool();
	
	bool operator==( const Bool& )const;
	bool operator!=( const Bool& )const;

	Bool& operator=( const Bool& );
	Bool& operator=( const type_name& b );
	
	type_name value() const override;

	string toString() const override; 
};
