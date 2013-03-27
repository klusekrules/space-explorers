#pragma once
#include "Main.h"
#include <vector>
#include <memory>
#include "ZmianaInterfejs.h"
#include "parser\ticpp.h"

class ZmianaAgregacja :
	public ZmianaInterfejs,
	public LoggerInterface<ZmianaAgregacja>
{
private:
	vector<shared_ptr < ZmianaInterfejs > > list;
public:
	//Metoda docelowo do przeprojektowania
	long double value(const long double&) const override {
		return long double(0);
	}
	//-------------------------------------------
	ZmianaAgregacja( const ticpp::Element* );
	~ZmianaAgregacja();
};

