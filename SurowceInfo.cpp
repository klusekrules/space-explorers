#include "SurowceInfo.h"
#include "Logger.h"
#include "XmlBO.h"
#include "Aplikacja.h"
#include "definicjeWezlowXML.h"

SurowceInfo::~SurowceInfo(){
}

SurowceInfo::SurowceInfo( TiXmlElement* wezel ) throw(WyjatekParseraXML)
	: ObiektInfo(wezel) , przyrostowy_ (false), zmianaCzasu_(nullptr)
{
	if(wezel){
		zmianaCzasu_ = Utils::TworzZmiane(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel,WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,WEZEL_XML_CZAS));
		auto przyrostowy = XmlBO::WczytajAtrybut<int>(wezel,ATRYBUT_XML_TYP,0);
		switch(przyrostowy){
		case 1 : przyrostowy_ = true;
			break;
		case 2 : przyrostowy_ = false;
			break;
		default: Utils::generujWyjatekBleduStruktury(EXCEPTION_PLACE,wezel);
		}
	}
}

bool SurowceInfo::czyTypPrzyrostowy()const{
	return przyrostowy_();
}

bool SurowceInfo::tworz( const Gra& gra, Planeta& planeta , const Ilosc& ilosc ) const{
	return gra.wybudujNaPlanecie(planeta,*this,ilosc);
}

Czas SurowceInfo::pobierzCzas( const Ilosc& ilosc ,const PodstawoweParametry& parametryPodstawowe )const{
	if(zmianaCzasu_)
		return Czas(zmianaCzasu_->policzWartosc(ilosc(),static_cast<int>(parametryPodstawowe.pobierzPoziom()()),parametryPodstawowe.pobierzIdentyfikatorPlanety()()));
	else
		return Czas(0.0l);
}

Surowce* SurowceInfo::tworzEgzemplarz( const Ilosc& ilosc, const Identyfikator& identyfikatorPlanety ) const{
	return new Surowce( ilosc , pobierzPoziom(),identyfikatorPlanety, *this );
}

string SurowceInfo::napis() const{
	Logger str(NAZWAKLASY(SurowceInfo));
	str.dodajKlase(ObiektInfo::napis());
	str.dodajPole("CzyPrzyrostowy",przyrostowy_);
	if(zmianaCzasu_)
		str.dodajPole("ZmianaCzasu",*zmianaCzasu_);
	return str.napis();
}
