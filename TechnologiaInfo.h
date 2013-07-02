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
	explicit TechnologiaInfo( ticpp::Node* );
	Technologia* TworzEgzemplarz( const Ilosc&, const IdType& ) const override;
	~TechnologiaInfo( );
	string toString()const override;
};

