#pragma once
#include "Main.h"
#include "Info.h"
#include "Ladownia.h"
#include "ZmianaInterfejs.h"

class LadowniaInfo :
	public Info,
	public LoggerInterface<LadowniaInfo>
{
private:
	
	Objetosc pojemnoscMax;
	ZmianaInterfejs<Objetosc>* przyrostPojemnoscMax;

public:
	typedef LoggerInterface<LadowniaInfo> LogLadowniaInfo;

	LadowniaInfo( const Objetosc& max, const Info& i );
	virtual ~LadowniaInfo();

	Objetosc getPojemnoscMaksymalna() const;
		
	string toString() const override;
};

