#pragma once
#include "Main.h"
#include "ObiektInfo.h"
#include "Surowce.h"

class SurowceInfo : 
	virtual public Base,
	public ObiektInfo,
	public LoggerInterface<SurowceInfo>
{
public:
	typedef LoggerInterface<SurowceInfo> LogSurowceInfo;
	
	explicit SurowceInfo( const ObiektInfo& );
	
	virtual ~SurowceInfo();
	
	Surowce* TworzEgzemplarz( const Ilosc& ) const override;

	string toString() const override;
};
