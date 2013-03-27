#pragma once
#include "Main.h"
#include "parser\ticpp.h"
#include "ZmianaInterfejs.h"

class ZmianaFabryka
{
public:
	static ZmianaFabryka& pobierzInstancje();
	
	shared_ptr<ZmianaInterfejs> Tworz( const ticpp::Element* );

	~ZmianaFabryka();
private:
	ZmianaFabryka();
};

