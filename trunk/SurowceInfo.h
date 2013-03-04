#pragma once
#include "Main.h"
#include "ObiektInfo.h"
#include "Surowce.h"

class SurowceInfo : 
	public ObiektInfo,
	public LoggerInterface<SurowceInfo>
{
public:
	typedef LoggerInterface<SurowceInfo> LogSurowceInfo;

	SurowceInfo();

	explicit SurowceInfo( const ObiektInfo& );

	SurowceInfo( const SurowceInfo& );

	virtual ~SurowceInfo();
	
	Surowce* TworzEgzemplarz( const Ilosc& ) const override;

	string toString() const override;
};
