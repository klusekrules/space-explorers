#pragma once
#include "FuncTransf\ZmianaFabryka.h"
#include "FuncTransf\ZmianaParametr.h"

class ZmianaPoziomObiektu:
	public ZmianaInterfejs,
	virtual public LoggerInterface
{
private:
	static const int idKlasy;
	static ZmianaInterfejs* TworzZmianaPoziomObiektu( TiXmlElement* e ){
		return new ZmianaPoziomObiektu(e);
	}
public:	
	static bool RejestrujZmianaPoziomObiektu( ZmianaFabryka &ref );

private:
	ZmianaParametr parametr;
public:
	long double policzWartosc(long double wartosc, int poziom, int identyfikatorPlanety) const override;

	ZmianaPoziomObiektu* Kopia()const override;

	explicit ZmianaPoziomObiektu( TiXmlElement * e );
	virtual ~ZmianaPoziomObiektu(void);

	string toString () const override;

};

bool RejestrujZmianaPoziomObiektu ( ZmianaFabryka& fabryka , Log& logger );
