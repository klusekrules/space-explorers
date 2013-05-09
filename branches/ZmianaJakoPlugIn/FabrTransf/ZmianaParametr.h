#pragma once
#include "stdafx.h"
#include "../BaseTypes/IdType.h"
#include "../BaseTypes/Parametr.h"
#include "../parser/ticpp.h"

class FABRTRANSF_API ZmianaParametr :
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

