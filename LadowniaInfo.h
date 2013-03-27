#pragma once
#include "Main.h"
#include "Info.h"
#include "Ladownia.h"
#include "ZmianaInterfejs.h"
#include "WyjatekParseraXML.h"

class LadowniaInfo :
	public Info,
	public LoggerInterface<LadowniaInfo>
{
private:
	
	Objetosc pojemnoscMax;
	ZmianaInterfejs* przyrostPojemnoscMax;

public:
	typedef LoggerInterface<LadowniaInfo> LogLadowniaInfo;

	LadowniaInfo( const Objetosc& max, const Info& i );

	LadowniaInfo( ticpp::Node* );

	virtual ~LadowniaInfo();

	Objetosc getPojemnoscMaksymalna() const;
		
	string toString() const override;
};

