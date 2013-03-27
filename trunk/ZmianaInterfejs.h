#pragma once
#include "LoggerInterface.h"
#include "Logger.h"

class ZmianaInterfejs: 
	public LoggerInterface<ZmianaInterfejs>
{
public:
	virtual long double value(const long double&) const = 0;
	ZmianaInterfejs(){}
	virtual ~ZmianaInterfejs(){}

	string toString() const override{
		Logger str(className());
		return str.toString();
	}
};

