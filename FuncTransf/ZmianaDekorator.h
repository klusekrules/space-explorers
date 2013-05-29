#pragma once
#include <memory>
#include "ZmianaInterfejs.h"
#include "..\parser\ticpp.h"
using std::shared_ptr;
class ZmianaDekorator:
	public ZmianaInterfejs,
	virtual public LoggerInterface
{
private:
	static const int idKlasy;
	static ZmianaInterfejs* TworzZmianaDekorator( const ticpp::Element* e ){
		return new ZmianaDekorator(e);
	}
public:	
	static bool RejestrujZmianaDekotor();
	
private:
	shared_ptr<ZmianaInterfejs> next;

public:	
	long double value( const long double& , const int&)const override;

	explicit ZmianaDekorator( const ticpp::Element* e );
	ZmianaDekorator( const ZmianaDekorator& e );

	ZmianaDekorator* Kopia()const override;

	ZmianaDekorator& operator=(const ZmianaDekorator& );

	virtual ~ZmianaDekorator();
	
	string toString () const override;
};

