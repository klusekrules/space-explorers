#pragma once
#include <memory>
#include "ZmianaInterfejs.h"
#include "Logger.h"
#include "parser\ticpp.h"

class ZmianaDekorator:
	public ZmianaInterfejs,
	public LoggerInterface<ZmianaDekorator>
{
private:
	shared_ptr<ZmianaInterfejs> next;
public:
	typedef LoggerInterface<ZmianaDekorator> LogZmianaDekorator;
	//Metoda docelowo do usuniêcia
	long double value(const long double&) const override {
		return long double(0);
	}
	//-------------------------------------------

	ZmianaDekorator(  const ticpp::Element* e ){

	}

	virtual ~ZmianaDekorator(){
	}

	string toString () const override{
		Logger str(LogZmianaDekorator::className());
		str.addClass(ZmianaInterfejs::toString());
		return str.toString();
	}
};

