#pragma once
#include "Main.h"
#include "ObiektInfo.h"
#include "Surowce.h"
#include "WyjatekParseraXML.h"
#include "Bool.h"

class SurowceInfo :
	public ObiektInfo,
	virtual public LoggerInterface
{
public:
	SurowceInfo( const ObiektInfo& , bool bCzyPrzyrostowy) throw();

	explicit SurowceInfo( ticpp::Node* ) throw(WyjatekParseraXML);
	
	virtual ~SurowceInfo();

	bool czyTypPrzyrostowy()const;
	
	Surowce* TworzEgzemplarz( const Ilosc&, const IdType& ) const override;

	string toString() const override;

	Czas pobierzCzas( const Ilosc& ,const PodstawoweParametry& )const;

private:

	Bool czyPrzyrostowy;

	shared_ptr<ZmianaInterfejs> zmCzas;

};
