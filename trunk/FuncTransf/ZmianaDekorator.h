#pragma once
#include "ExportSymbol.h"
#include <memory>
#include "ZmianaInterfejs.h"
#include "..\parser\ticpp.h"
#include "ZmianaFabryka.h"
using std::shared_ptr;
class FUNCTRANSF_API ZmianaDekorator:
	public ZmianaInterfejs,
	virtual public LoggerInterface
{
private:
	static ZmianaFabryka* zFabryka;
	static const int idKlasy;
	static ZmianaInterfejs* TworzZmianaDekorator( const ticpp::Element* e ){
		return new ZmianaDekorator(e);
	}
public:	
	static bool RejestrujZmianaDekotor( ZmianaFabryka &ref );
	
private:
	shared_ptr<ZmianaInterfejs> next;

public:	
	long double value( const long double& , const int&, const int&)const override;

	explicit ZmianaDekorator( const ticpp::Element* e );
	ZmianaDekorator( const ZmianaDekorator& e );

	ZmianaDekorator* Kopia()const override;

	ZmianaDekorator& operator=(const ZmianaDekorator& );

	virtual ~ZmianaDekorator();
	
	string toString () const override;
};

