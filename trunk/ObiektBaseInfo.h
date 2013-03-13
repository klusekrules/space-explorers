#pragma once
#include "Main.h"
#include "Info.h"
#include "Poziom.h"

class ObiektBaseInfo:
	public Info,
	public LoggerInterface<ObiektBaseInfo>
{
public:
	typedef LoggerInterface<ObiektBaseInfo> LogObiektBaseInfo;

	ObiektBaseInfo( const Info& i , const Poziom& p );

	virtual ~ObiektBaseInfo();
	
	virtual ObiektBase* TworzEgzemplarz( const Ilosc& ) const;

	const Poziom& getPoziom()const;

	string toString() const;

private:
	Poziom poziom;
};

