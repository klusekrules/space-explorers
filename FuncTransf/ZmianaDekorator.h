#pragma once
#include "stdafx.h"
#include <memory>
#include "../FabrTransf/FabrTransf.h"
#include "../parser/ticpp.h"
#include "../BaseTypes/IdType.h"

class FUNCTRANSF_API ZmianaDekorator:
	public ZmianaInterfejs,
	virtual public LoggerInterface
{
private:
	static const IdType idKlasy;
	static ZmianaInterfejs* TworzZmianaDekorator( const ticpp::Element* e ){
		return new ZmianaDekorator(e);
	}
public:	
	static bool RejestrujZmianaDekotor();
	
private:
	shared_ptr<ZmianaInterfejs> next;

public:	
	long double value( const long double& , const Poziom&)const override;

	explicit ZmianaDekorator( const ticpp::Element* e );
	ZmianaDekorator( const ZmianaDekorator& e );

	ZmianaDekorator* Kopia()const override;

	ZmianaDekorator& operator=(const ZmianaDekorator& );

	virtual ~ZmianaDekorator();
	
	string toString () const override;
};

