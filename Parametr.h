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

	void setParametr( const type_name& );

	string toString() const override;
};

