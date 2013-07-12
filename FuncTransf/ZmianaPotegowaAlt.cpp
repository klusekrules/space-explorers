#include "ZmianaPotegowaAlt.h"
#include "..\Logger\Logger.h"
#include "ZmianaFabryka.h"
#include "..\XmlBO.h"
#include "..\definicjeWezlowXML.h"

ZmianaPotegowaAlt::ZmianaPotegowaAlt( TiXmlElement * wezel ) throw(int)
	: wspolczynnik_(XmlBO::ZnajdzWezel<NOTHROW>( wezel, WEZEL_XML_PARAM )), wykladnik_(nullptr)
{
	if(fabryka_)
		wykladnik_ = fabryka_->Tworz(XmlBO::ZnajdzWezel<NOTHROW>( wezel, WEZEL_XML_ZMIANA ));
}

ZmianaPotegowaAlt::~ZmianaPotegowaAlt(void){
}

ZmianaInterfejs* ZmianaPotegowaAlt::TworzZmianaPotegowaAlt( TiXmlElement* wezel ){
	return new ZmianaPotegowaAlt(wezel);
}

long double ZmianaPotegowaAlt::policzWartosc(long double wartosc, int poziom, int identyfikatorPlanety) const{
	if(wykladnik_)
		return wartosc * pow( static_cast<long double>(wspolczynnik_.pobierzWspolczynnik()), -(wykladnik_->policzWartosc( wartosc, poziom, identyfikatorPlanety )) );
	else
		return wartosc;
}

ZmianaPotegowaAlt* ZmianaPotegowaAlt::Kopia()const{
	return new ZmianaPotegowaAlt(*this);
}

bool ZmianaPotegowaAlt::RejestrujZmianaPotegowaAlt( ZmianaFabryka &fabryka ){
	fabryka_ = &fabryka;
	return fabryka.rejestracjaZmiany( identyfikator_, ZmianaPotegowaAlt::TworzZmianaPotegowaAlt );
}

string ZmianaPotegowaAlt::toString()const{
	Logger str(NAZWAKLASY(ZmianaPotegowaAlt));
	str.dodajPole( "wspolczynnik", wspolczynnik_ );
	if(wykladnik_)
		str.dodajPole( "wykladnik", *wykladnik_ );
	return str.toString();
}
