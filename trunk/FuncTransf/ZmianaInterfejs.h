#pragma once
#include "ExportSymbol.h"
#include "..\Logger\LoggerInterface.h"

class FUNCTRANSF_API ZmianaInterfejs: 
	virtual public LoggerInterface
{
public:
	virtual long double value(const long double&, const int&, const int&) const = 0;
	virtual ZmianaInterfejs* Kopia() const = 0;
	ZmianaInterfejs();
	virtual ~ZmianaInterfejs();
};

