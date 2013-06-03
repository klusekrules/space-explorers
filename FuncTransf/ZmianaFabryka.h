#pragma once
#include "ExportSymbol.h"
#include "..\parser\ticpp.h"
#include "ZmianaInterfejs.h"
#include <map>
#include <memory>
using std::shared_ptr;
using std::map;

class FUNCTRANSF_API ZmianaFabryka
{
public:
	typedef ZmianaInterfejs* (*KreatorZmiany)( const ticpp::Element* );

	static ZmianaFabryka& pobierzInstancje();
	
	shared_ptr<ZmianaInterfejs> Tworz( const ticpp::Element* );

	bool RejestracjaZmiany(int id, KreatorZmiany fun);

	~ZmianaFabryka();
private:
	typedef map<int, KreatorZmiany> Callbacks;
	Callbacks callbacks_;
	ZmianaFabryka();
	ZmianaFabryka( const ZmianaFabryka& a);
	ZmianaFabryka& operator=(const ZmianaFabryka& a);
};

