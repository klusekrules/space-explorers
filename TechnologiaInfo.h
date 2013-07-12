#pragma once

#include "ObiektBaseInfo.h"
#include "Technologia.h"

class TechnologiaInfo : 
	public ObiektBaseInfo,
	virtual public LoggerInterface
{
public:
	TechnologiaInfo( const TechnologiaInfo& );
	explicit TechnologiaInfo( const ObiektBaseInfo& );
	explicit TechnologiaInfo( TiXmlElement* );
	Technologia* TworzEgzemplarz( const Ilosc&, const Identyfikator& ) const override;
	~TechnologiaInfo( );
	string napis()const override;
private:
	bool Tworz( const Gra& g, Planeta& p , const Ilosc& i ) const override;
};

