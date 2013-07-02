#pragma once
#include "Main.h"
#include "Info.h"
#include "Ladownia.h"
#include "FuncTransf\ZmianaInterfejs.h"
#include "WyjatekParseraXML.h"

class LadowniaInfo :
	public Info,
	virtual public LoggerInterface
{
private:
	
	Objetosc pojemnoscMax;
	shared_ptr<ZmianaInterfejs> przyrostPojemnoscMax;

public:
	LadowniaInfo( const Objetosc& max, const Info& i ) throw();

	explicit LadowniaInfo( ticpp::Node* ) throw(WyjatekParseraXML);

	virtual ~LadowniaInfo();

	Objetosc getPojemnoscMaksymalna( const Poziom& , const IdType&) const;
		
	string toString() const override;
};

