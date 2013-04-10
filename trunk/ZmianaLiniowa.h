#pragma once
#include "Main.h"
#include "ZmianaInterfejs.h"
#include "ZmianaParametr.h"

#include "parser\ticpp.h"

class WyjatekParseraXML;

class ZmianaLiniowa:
	public ZmianaInterfejs,
	public LoggerInterface< ZmianaLiniowa >
{
private:
	static const IdType idKlasy;
	static ZmianaInterfejs* TworzZmianaLiniowa( const ticpp::Element* e ){
		return new ZmianaLiniowa(e);
	}
public:	
	static bool RejestrujZmianaLiniowa();

private:
	ZmianaParametr parametr;
public:
	typedef LoggerInterface< ZmianaLiniowa > LogZmianaLiniowa;

	long double value(const long double&, const Poziom&) const override;

	ZmianaLiniowa* Kopia()const override;

	explicit ZmianaLiniowa( const ticpp::Element * e ) throw(WyjatekParseraXML);
	virtual ~ZmianaLiniowa(void);

	string toString () const override;

};