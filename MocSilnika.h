#pragma once
#include "Main.h"
#include "TypyProste.h"

class MocSilnika:
	virtual public LoggerInterface,
	public PodstawowyInterfejs<SPG::MocSilnika>
{
public:	
	MocSilnika();
	MocSilnika( const MocSilnika& );
	explicit MocSilnika( const type_name& );
	virtual ~MocSilnika();

	bool operator==( const MocSilnika& )const;
	bool operator!=( const MocSilnika& )const;
	bool operator<( const MocSilnika& )const;
	bool operator<=( const MocSilnika& )const;
	bool operator>( const MocSilnika& )const;
	bool operator>=( const MocSilnika& )const;

	MocSilnika& operator=( const MocSilnika& );
	MocSilnika& operator-=( const MocSilnika& );
	MocSilnika& operator+=( const MocSilnika& );
	MocSilnika operator-( const MocSilnika& )const;
	MocSilnika operator+( const MocSilnika& )const;
	
	string napis() const override; 
};


