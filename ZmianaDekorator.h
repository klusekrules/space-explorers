#pragma once

#include "ZmianaInterfejs.h"
#include "Logger.h"

template < class T >
class ZmianaDekorator:
	public ZmianaInterfejs<T>,
	public LoggerInterface<ZmianaDekorator<T>>
{
private:
	ZmianaInterfejs* next;
public:
	typedef LoggerInterface<ZmianaDekorator<T>> LogZmianaDekorator;
	//Metoda docelowo do usuniêcia
	T value(const T&) const override {
		return T();
	}
	//-------------------------------------------

	ZmianaDekorator( ZmianaInterfejs* a ) : next(a) {}

	virtual ~ZmianaDekorator(){
		if(next!=nullptr)
			delete next;
	}

	string toString const override{
		Logger str(LogZmianaDekorator::className());
		str.addClass(ZmianaInterfejs<T>::toString());
		return str.toString();
	}
};

