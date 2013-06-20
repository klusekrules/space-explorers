#pragma once
#include "ExportSymbol.h"
#include <vector>
#include <memory>
#include "ZmianaDekorator.h"
#include "..\parser\ticpp.h"
#include "..\Logger\LoggerInterface.h"
#include "ZmianaFabryka.h"
using std::vector;
using std::shared_ptr;
class FUNCTRANSF_API ZmianaAgregacja :
	public ZmianaDekorator,
	virtual public LoggerInterface
{
private:
	static ZmianaFabryka* zFabryka;
	static const int idKlasy;
	static ZmianaInterfejs* TworzZmianaAgregacja( const ticpp::Element* e ){
		return new ZmianaAgregacja(e);
	}
public:	
	static bool RejestrujZmianaAgregacja( ZmianaFabryka &ref );

private:
	vector<shared_ptr < ZmianaInterfejs > > list;

public:
	
	long double value( const long double& , const int& )const override;

	explicit ZmianaAgregacja( const ticpp::Element* );

	ZmianaAgregacja( const ZmianaAgregacja& );

	ZmianaAgregacja& operator=( const ZmianaAgregacja& );

	ZmianaAgregacja* Kopia()const override;

	virtual ~ZmianaAgregacja();

	string toString() const override;
};

