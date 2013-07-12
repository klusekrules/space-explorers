#pragma once
#include "Main.h"
#include "BaseTypes.h"

class Parametr:
	virtual public LoggerInterface,
	public BaseInterface<SPG::Parametr>
{
public:
	Parametr();
	explicit Parametr( const type_name& );
	Parametr( const Parametr& );
	virtual ~Parametr();

	Parametr& operator=( const Parametr& );
	
	string napis() const override;
};

