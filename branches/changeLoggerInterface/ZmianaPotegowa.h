#pragma once
#include "Main.h"
#include "ZmianaInterfejs.h"
#include "ZmianaParametr.h"

class WyjatekParseraXML;

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

	explicit ZmianaPotegowa( const ticpp::Element * e ) throw(WyjatekParseraXML);
	virtual ~ZmianaPotegowa(void);

	string toString () const override;

};