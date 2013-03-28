#pragma once
#include <memory>
#include "Main.h"
#include "ZmianaInterfejs.h"
#include "Logger.h"
#include "parser\ticpp.h"
#include "IdType.h"

class ZmianaDekorator:
	public ZmianaInterfejs,
	public LoggerInterface<ZmianaDekorator>
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
	typedef LoggerInterface<ZmianaDekorator> LogZmianaDekorator;
	
	long double value( const long double& )const override;

	explicit ZmianaDekorator( const ticpp::Element* e );
	ZmianaDekorator( const ZmianaDekorator& e );

	ZmianaDekorator* Kopia()const override;

	ZmianaDekorator& operator=(const ZmianaDekorator& );

	virtual ~ZmianaDekorator();
	
	string toString () const override;
};

