#pragma once
#include "..\parser\ticpp.h"
#include "..\Logger\LoggerInterface.h"
class ZmianaParametr:
	virtual public LoggerInterface
{
private:
	int idObiektu;
	long double wspolczynnikObiektu;
public:
	ZmianaParametr( const ticpp::Element* e );
	virtual ~ZmianaParametr(void);

	int getIdObiektu()const{
		return idObiektu;
	}

	long double getWspolczynnik()const{
		return wspolczynnikObiektu;
	}
	
	string toString () const override;
};

