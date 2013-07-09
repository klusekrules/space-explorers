#pragma once
#include "ExportSymbol.h"
#include "..\parser\ticpp.h"
#include "..\Logger\LoggerInterface.h"
class FUNCTRANSF_API ZmianaParametr:
	virtual public LoggerInterface
{
private:
	int idObiektu;
	long double wspolczynnikObiektu;
public:
	ZmianaParametr( TiXmlElement* e );
	virtual ~ZmianaParametr(void);

	int getIdObiektu()const{
		return idObiektu;
	}

	long double getWspolczynnik()const{
		return wspolczynnikObiektu;
	}
	
	string toString () const override;
};

