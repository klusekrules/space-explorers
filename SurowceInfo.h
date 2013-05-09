#pragma once
#include "Main.h"
#include "ObiektInfo.h"
#include "Surowce.h"
#include "BaseTypes\BaseTypes.h"
#include "BaseTypes\Wyjatki.h"

class SurowceInfo :
	public ObiektInfo,
	virtual public LoggerInterface
{
public:
	SurowceInfo( const ObiektInfo& , bool bCzyPrzyrostowy) throw();

	explicit SurowceInfo( ticpp::Node* ) throw(WyjatekParseraXML);
	
	virtual ~SurowceInfo();

	bool czyTypPrzyrostowy()const;
	
	Surowce* TworzEgzemplarz( const Ilosc& ) const override;

	string toString() const override;

private:

	Bool czyPrzyrostowy;

};
