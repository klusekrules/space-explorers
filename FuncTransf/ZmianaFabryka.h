#pragma once
#include "../parser\ticpp.h"
#include "ZmianaInterfejs.h"
#include "../BaseTypes\IdType.h"
#include <map>
#include "..\BaseTypes\WyjatekParseraXML.h"
#include "../BaseTypes\NieznalezionoObiektu.h"
#include "../BaseTypes\BrakAtrybutuXML.h"

class ZmianaFabryka
{
public:
	typedef ZmianaInterfejs* (*KreatorZmiany)( const ticpp::Element* );

	static ZmianaFabryka& pobierzInstancje();
	
	shared_ptr<ZmianaInterfejs> Tworz( const ticpp::Element* ) throw(BrakAtrybutuXML,NieznalezionoObiektu,OgolnyWyjatek);

	bool RejestracjaZmiany(IdType id, KreatorZmiany fun);

	~ZmianaFabryka();
private:
	typedef map<IdType, KreatorZmiany> Callbacks;
	Callbacks callbacks_;
	ZmianaFabryka();
	ZmianaFabryka( const ZmianaFabryka& a);
	ZmianaFabryka& operator=(const ZmianaFabryka& a);
};

