#pragma once
#include "Main.h"
#include "Info.h"
#include "Ladownia.h"
#include "FabrTransf\ZmianaInterfejs.h"
#include "BaseTypes\BaseTypes.h"
#include "BaseTypes\Wyjatki.h"

class LadowniaInfo :
	public Info,
	virtual public LoggerInterface
{
private:
	
	Objetosc pojemnoscMax;
	ZmianaInterfejs* przyrostPojemnoscMax;

public:
	LadowniaInfo( const Objetosc& max, const Info& i ) throw();

	explicit LadowniaInfo( ticpp::Node* ) throw(WyjatekParseraXML);

	virtual ~LadowniaInfo();

	Objetosc getPojemnoscMaksymalna( const Poziom& ) const;
		
	string toString() const override;
};

