#pragma once
#include "../BaseTypes\Poziom.h"
#pragma warning( disable : 4290 )
class ZmianaInterfejs: 
	virtual public LoggerInterface
{
public:
	virtual long double value(const long double&, const Poziom&) const = 0;
	virtual ZmianaInterfejs* Kopia() const = 0;
	ZmianaInterfejs();
	virtual ~ZmianaInterfejs();
};

