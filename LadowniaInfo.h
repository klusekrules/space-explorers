#pragma once
#include "Main.h"
#include "Info.h"
#include "Ladownia.h"
#include "FuncTransf\ZmianaInterfejs.h"
#include "WyjatekParseraXML.h"
#include "PodstawoweParametry.h"

class LadowniaInfo :
	public Info,
	virtual public LoggerInterface
{
private:
	
	Objetosc pojemnoscMax;
	shared_ptr<ZmianaInterfejs> przyrostPojemnoscMax;

public:
	LadowniaInfo( const Objetosc& max, const Info& i ) throw();

	explicit LadowniaInfo( TiXmlElement* ) throw(WyjatekParseraXML);
	
	Objetosc getPojemnoscMaksymalna( const PodstawoweParametry& ) const;
		
	string napis() const override;
};

