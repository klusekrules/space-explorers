#pragma once
#include "Logger\LoggerInterface.h" 
#include "Main.h"
#include "BaseTypes.h"

class Czas:
	public LoggerInterface,
	public BaseInterface< SPG::Czas >
{
public:	
	Czas();
	Czas( const Czas& );
	explicit Czas( const type_name& );
	virtual ~Czas();
	
	bool operator==( const Czas& )const;
	bool operator!=( const Czas& )const;

	Czas& operator=( const Czas& );
	Czas& operator+=( const Czas& );
	Czas& operator=( const type_name& b );
	
	string toString() const override;		 
};
