#pragma once
#include "Main.h"
#include "ObiektInfo.h"
#include "Surowce.h"
#include "WyjatekParseraXML.h"

class SurowceInfo :
	public ObiektInfo,
	public LoggerInterface<SurowceInfo>
{
public:
	typedef LoggerInterface<SurowceInfo> LogSurowceInfo;
	
	explicit SurowceInfo( const ObiektInfo& );

	explicit SurowceInfo( ticpp::Node* );
	
	virtual ~SurowceInfo();
	
	Surowce* TworzEgzemplarz( const Ilosc& ) const override;

	string toString() const override;
};
