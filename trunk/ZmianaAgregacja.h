#pragma once
#include "Main.h"
#include <vector>
#include <memory>
#include "ZmianaDekorator.h"
#include "parser\ticpp.h"
#include "IdType.h"

class ZmianaAgregacja :
	public ZmianaDekorator,
	public LoggerInterface<ZmianaAgregacja>
{
private:
	static const IdType idKlasy;
	static ZmianaInterfejs* TworzZmianaAgregacja( const ticpp::Element* e ){
		return new ZmianaAgregacja(e);
	}
public:	
	static bool RejestrujZmianaAgregacja();

private:
	vector<shared_ptr < ZmianaInterfejs > > list;

public:
	typedef LoggerInterface<ZmianaAgregacja> LogZmianaAgregacja;
	
	long double value( const long double& )const override;

	explicit ZmianaAgregacja( const ticpp::Element* );

	ZmianaAgregacja( const ZmianaAgregacja& );

	ZmianaAgregacja& operator=( const ZmianaAgregacja& );

	ZmianaAgregacja* Kopia()const override;

	virtual ~ZmianaAgregacja();

	string toString() const override;
};

