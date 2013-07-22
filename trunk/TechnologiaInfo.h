#pragma once
#include "ObiektBazowyInfo.h"
#include "Technologia.h"

class TechnologiaInfo : 
	public ObiektBazowyInfo,
	virtual public LoggerInterface
{
public:
	TechnologiaInfo( const TechnologiaInfo& );
	explicit TechnologiaInfo( const ObiektBazowyInfo& );
	explicit TechnologiaInfo( TiXmlElement* );
	Technologia* tworzEgzemplarz( const Ilosc&, const Identyfikator& ) const override;
	~TechnologiaInfo( );
	string napis()const override;
private:
	bool tworz( const Gra& g, Planeta& p , const Ilosc& i ) const override;
};

