#pragma once
#include "Main.h"
#include "BaseTypes.h"

class Parametr:
	public LoggerInterface<Parametr>,
	public BaseInterface<SPG::Parametr>
{
private:
	type_name parametr;
public:
	Parametr();
	explicit Parametr( const type_name& );
	Parametr( const Parametr& );
	virtual ~Parametr();

	Parametr& operator=( const Parametr& );

	void setParametr( const type_name& );
	
	type_name value() const override;

	string toString() const override;
};
