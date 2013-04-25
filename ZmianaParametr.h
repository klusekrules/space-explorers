#pragma once
#include "Main.h"
#include "IdType.h"
#include "Parametr.h"
#include "parser\ticpp.h"

class ZmianaParametr:
	virtual public LoggerInterface
{
private:
	IdType idObiektu;
	Parametr wspolczynnikObiektu;
public:
	ZmianaParametr( const ticpp::Element* e );
	virtual ~ZmianaParametr(void);

	const IdType& getIdObiektu()const{
		return idObiektu;
	}

	const Parametr& getWspolczynnik()const{
		return wspolczynnikObiektu;
	}
	
	string toString () const override;
};

