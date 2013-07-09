#pragma once
#include "ExportSymbol.h"
#include <vector>
#include <memory>
#include "..\parser\ticpp.h"
#include "..\Logger\LoggerInterface.h"
#include "ZmianaFabryka.h"
using std::vector;
using std::shared_ptr;
class FUNCTRANSF_API ZmianaAgregacja :
	public ZmianaInterfejs,
	virtual public LoggerInterface
{
private:
	static ZmianaFabryka* zFabryka;
	static const int idKlasy;
	static ZmianaInterfejs* TworzZmianaAgregacja( TiXmlElement* e ){
		return new ZmianaAgregacja(e);
	}
public:	
	static bool RejestrujZmianaAgregacja( ZmianaFabryka &ref );

private:
	shared_ptr < ZmianaInterfejs > next;
	vector<shared_ptr < ZmianaInterfejs > > list;

public:
	
	long double value( const long double& , const int&, const int& )const override;

	explicit ZmianaAgregacja( TiXmlElement* );

	ZmianaAgregacja( const ZmianaAgregacja& );

	ZmianaAgregacja& operator=( const ZmianaAgregacja& );

	ZmianaAgregacja* Kopia()const override;

	virtual ~ZmianaAgregacja();

	string toString() const override;
};

