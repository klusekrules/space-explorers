#pragma once

#include "ZmianaInterfejs.h"
#include "Logger.h"

template < class T >
class Zmiana:
	public ZmianaInterfejs<T>,
	public LoggerInterface<Zmiana<T>>
{
public:
	typedef LoggerInterface<Zmiana<T>> LogZmiana;
	T value( const T& ) const override {
		return T();
	}
	Zmiana(){}
	virtual ~Zmiana(){}

	string toString() const override{
		Logger str(LogZmiana::className());
		str.addClass(ZmianaInterfejs<T>::toString());
		return str.toString();
	}
};

