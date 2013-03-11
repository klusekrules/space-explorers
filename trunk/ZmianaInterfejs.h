#pragma once
#include "LoggerInterface.h"
#include "Logger.h"

template < class T >
class ZmianaInterfejs: 
	public LoggerInterface<ZmianaInterfejs<T>>
{
public:
	virtual T value(const T&) const = 0;
	ZmianaInterfejs(){}
	virtual ~ZmianaInterfejs(){}

	string toString() const override{
		Logger str(className());
		return str.toString();
	}
};

