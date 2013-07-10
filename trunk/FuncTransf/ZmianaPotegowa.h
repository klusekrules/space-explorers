#pragma once
#include "ExportSymbol.h"
#include "..\parser\ticpp.h"
#include "ZmianaInterfejs.h"
#include "ZmianaParametr.h"
#include "ZmianaFabryka.h"
class FUNCTRANSF_API ZmianaPotegowa:
	public ZmianaInterfejs,
	virtual public LoggerInterface
{
private:
	static const int idKlasy;
	static ZmianaInterfejs* TworzZmianaPotegowa( TiXmlElement* e ){
		return new ZmianaPotegowa(e);
	}
public:	
	static bool RejestrujZmianaPotegowa( ZmianaFabryka &ref  );

private:
	ZmianaParametr wspolczynnik;
	ZmianaParametr wykladnik;
public:

	long double policzWartosc(long double wartosc, int poziom, int identyfikatorPlanety) const override;

	ZmianaPotegowa* Kopia()const override;

	explicit ZmianaPotegowa( TiXmlElement * e );
	virtual ~ZmianaPotegowa(void);

	string toString () const override;

};