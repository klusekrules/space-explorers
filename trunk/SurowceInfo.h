#pragma once
#include "Main.h"
#include "ObiektInfo.h"
#include "Surowce.h"
#include "WyjatekParseraXML.h"
#include "Bool.h"

class SurowceInfo :
	public ObiektInfo,
	public LoggerInterface<SurowceInfo>
{
public:
	typedef LoggerInterface<SurowceInfo> LogSurowceInfo;
	
	SurowceInfo( const ObiektInfo& , bool bCzyPrzyrostowy) throw();

	explicit SurowceInfo( ticpp::Node* ) throw(WyjatekParseraXML);
	
	virtual ~SurowceInfo();

	bool czyTypPrzyrostowy()const;
	
	Surowce* TworzEgzemplarz( const Ilosc& ) const override;

	string toString() const override;

private:

	Bool czyPrzyrostowy;

};