#pragma once
#include "FuncTransf\ZmianaFabryka.h"
#include "FuncTransf\ZmianaParametr.h"

class ZmianaPoziomObiektu:
	public ZmianaInterfejs,
	virtual public LoggerInterface
{
private:
	static const int idKlasy;
	static ZmianaInterfejs* TworzZmianaPoziomObiektu( const ticpp::Element* e ){
		return new ZmianaPoziomObiektu(e);
	}
public:	
	static bool RejestrujZmianaPoziomObiektu( ZmianaFabryka &ref );

private:
	ZmianaParametr parametr;
public:
	long double value(const long double&, const int&, const int&) const override;

	ZmianaPoziomObiektu* Kopia()const override;

	explicit ZmianaPoziomObiektu( const ticpp::Element * e );
	virtual ~ZmianaPoziomObiektu(void);

	string toString () const override;

};

bool RejestrujZmianaPoziomObiektu ( ZmianaFabryka& fabryka , Log& logger );
