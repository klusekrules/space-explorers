#pragma once
#include "Logger\LoggerInterface.h" 
#include "Main.h"
#include "TypyProste.h"

class Czas:
	public LoggerInterface,
	public PodstawowyInterfejs< SPG::Czas >
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
	
	string napis() const override;		 
};

