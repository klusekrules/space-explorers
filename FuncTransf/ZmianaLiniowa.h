#pragma once
#include "ZmianaInterfejs.h"
#include "ZmianaParametr.h"

#include "../parser/ticpp.h"
#include "../BaseTypes/WyjatekParseraXML.h"

class ZmianaLiniowa:
	public ZmianaInterfejs,
	virtual public LoggerInterface
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
	long double value(const long double&, const Poziom&) const override;

	ZmianaLiniowa* Kopia()const override;

	explicit ZmianaLiniowa( const ticpp::Element * e ) throw(WyjatekParseraXML);
	virtual ~ZmianaLiniowa(void);

	string toString () const override;

};