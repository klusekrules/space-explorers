#pragma once
#include "ZmianaInterfejs.h"
#include "ZmianaParametr.h"

class WyjatekParseraXML;

class ZmianaPotegowa:
	public ZmianaInterfejs,
	virtual public LoggerInterface
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

	long double value(const long double&, const Poziom&) const override;

	ZmianaPotegowa* Kopia()const override;

	explicit ZmianaPotegowa( const ticpp::Element * e ) throw(WyjatekParseraXML);
	virtual ~ZmianaPotegowa(void);

	string toString () const override;

};