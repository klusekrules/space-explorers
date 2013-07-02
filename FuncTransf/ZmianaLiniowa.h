#pragma once
#include "ExportSymbol.h"
#include "ZmianaInterfejs.h"
#include "ZmianaParametr.h"
#include "ZmianaFabryka.h"
#include "..\parser\ticpp.h"


class FUNCTRANSF_API ZmianaLiniowa:
	public ZmianaInterfejs,
	virtual public LoggerInterface
{
private:
	static const int idKlasy;
	static ZmianaInterfejs* TworzZmianaLiniowa( const ticpp::Element* e ){
		return new ZmianaLiniowa(e);
	}
public:	
	static bool RejestrujZmianaLiniowa( ZmianaFabryka &ref );

private:
	ZmianaParametr parametr;
public:
	long double value(const long double&, const int&, const int&) const override;

	ZmianaLiniowa* Kopia()const override;

	explicit ZmianaLiniowa( const ticpp::Element * e );
	virtual ~ZmianaLiniowa(void);

	string toString () const override;

};