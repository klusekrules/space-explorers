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

	explicit SurowceInfo( TiXmlElement* ) throw(WyjatekParseraXML);
	
	virtual ~SurowceInfo();

	bool czyTypPrzyrostowy()const;
	
	Surowce* TworzEgzemplarz( const Ilosc&, const IdType& ) const override;

	string toString() const override;

	Czas pobierzCzas( const Ilosc& ,const PodstawoweParametry& )const;

private:
	bool Tworz( const Gra& g, Planeta& p , const Ilosc& i ) const override;

	Bool czyPrzyrostowy;

	shared_ptr<ZmianaInterfejs> zmCzas;

};
