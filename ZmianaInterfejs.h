#pragma once
#include "Main.h"
#include "Poziom.h"

class ZmianaInterfejs: 
	public LoggerInterface<ZmianaInterfejs>
{
public:
	typedef LoggerInterface<ZmianaInterfejs> LogZmianaInterfejs;
	virtual long double value(const long double&, const Poziom&) const = 0;
	virtual ZmianaInterfejs* Kopia() const = 0;
	ZmianaInterfejs();
	virtual ~ZmianaInterfejs();
	string toString() const override;
};

