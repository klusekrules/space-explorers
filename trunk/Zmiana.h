#pragma once
#include "ZmianaInterfejs.h"
#include "Logger.h"
#include "parser\ticpp.h"

class Zmiana:
	public ZmianaInterfejs,
	public LoggerInterface<Zmiana>
{
public:
	typedef LoggerInterface<Zmiana> LogZmiana;
	long double value( const long double& ) const override {
		return long double();
	}
	Zmiana( const ticpp::Element* ){}
	virtual ~Zmiana(){}

	string toString() const override{
		Logger str(LogZmiana::className());
		str.addClass(ZmianaInterfejs::toString());
		return str.toString();
	}
};

