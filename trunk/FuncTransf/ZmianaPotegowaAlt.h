#pragma once
#include "ExportSymbol.h"
#include "..\parser\ticpp.h"
#include "ZmianaInterfejs.h"
#include "ZmianaParametr.h"
#include "ZmianaFabryka.h"
class FUNCTRANSF_API ZmianaPotegowaAlt:
	public ZmianaInterfejs,
	virtual public LoggerInterface
{
private:
	static ZmianaFabryka* zFabryka;
	static const int idKlasy;
	static ZmianaInterfejs* TworzZmianaPotegowaAlt( TiXmlElement* e ){
		return new ZmianaPotegowaAlt(e);
	}
public:	
	static bool RejestrujZmianaPotegowaAlt( ZmianaFabryka &ref  );

private:
	ZmianaParametr wspolczynnik;
	shared_ptr<ZmianaInterfejs> wykladnik;
public:

	long double value(const long double&, const int&, const int&) const override;

	ZmianaPotegowaAlt* Kopia()const override;

	explicit ZmianaPotegowaAlt( TiXmlElement * e );
	virtual ~ZmianaPotegowaAlt(void);

	string toString () const override;

};