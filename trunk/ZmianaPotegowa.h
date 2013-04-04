#pragma once
#include "Main.h"
#include "ZmianaInterfejs.h"
#include "ZmianaParametr.h"

class ZmianaPotegowa:
	public ZmianaInterfejs,
	public LoggerInterface< ZmianaPotegowa >
{
private:
	static const IdType idKlasy;
	static ZmianaInterfejs* TworzZmianaPotegowa( const ticpp::Element* e ){
		return new ZmianaPotegowa(e);
	}
public:	
	static bool RejestrujZmianaPotegowa();

private:
	ZmianaParametr wspolczynnik;
	ZmianaParametr wykladnik;
public:
	typedef LoggerInterface< ZmianaPotegowa > LogZmianaPotegowa;

	long double value(const long double&, const Poziom&) const override;

	ZmianaPotegowa* Kopia()const override;

	ZmianaPotegowa( const ticpp::Element * e );
	virtual ~ZmianaPotegowa(void);

	string toString () const override;

};