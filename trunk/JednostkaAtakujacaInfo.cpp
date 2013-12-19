#include "JednostkaAtakujacaInfo.h"
#include "Logger.h"
#include "XmlBO.h"
#include "Aplikacja.h"
#include "definicjeWezlowXML.h"
#include "Utils.h"

JednostkaAtakujacaInfo::JednostkaAtakujacaInfo(const Info& info, const Obrazenia& oAtak,const Obrazenia& oPancerz, const Obrazenia& oOslona) throw()
	: Info(info), atak_(oAtak), zmianaAtaku_(nullptr), pancerz_(oPancerz), zmianaPancerza_(nullptr), oslona_(oOslona), zmianaOslony_(nullptr)
{
}

JednostkaAtakujacaInfo::JednostkaAtakujacaInfo( tinyxml2::XMLElement* wezel ) throw(WyjatekParseraXML)
	: Info(wezel),zmianaAtaku_(nullptr), zmianaPancerza_(nullptr), zmianaOslony_(nullptr)
{
	if(wezel){
		try{
			XmlBO::WczytajAtrybut<THROW>(wezel,ATRYBUT_XML_ATAK,atak_);
			if( atak_ < Obrazenia(0) )
				throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(-1), Tekst("Nie poprawny atrybut."), Tekst("Atrybut \"atak\" posiada niepoprawn¹ wartoœæ.") );
			zmianaAtaku_ = Utils::TworzZmiane(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel,WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,ATRYBUT_XML_ATAK));

			XmlBO::WczytajAtrybut<THROW>(wezel,ATRYBUT_XML_PANCERZ,pancerz_);
			if( pancerz_ < Obrazenia(0) )
				throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(-1), Tekst("Nie poprawny atrybut."), Tekst("Atrybut \"pancerz\" posiada niepoprawn¹ wartoœæ.") );
			zmianaPancerza_ = Utils::TworzZmiane(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel,WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,ATRYBUT_XML_PANCERZ));

			XmlBO::WczytajAtrybut<THROW>(wezel,ATRYBUT_XML_OSLONA,oslona_);
			if( oslona_ < Obrazenia(0) )
				throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(-1), Tekst("Nie poprawny atrybut."), Tekst("Atrybut \"oslona\" posiada niepoprawn¹ wartoœæ.") );
			zmianaOslony_ = Utils::TworzZmiane(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel,WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,ATRYBUT_XML_OSLONA));
		}catch(exception& e){
			throw WyjatekParseraXML(EXCEPTION_PLACE,e,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}
}

JednostkaAtakujacaInfo::JednostkaAtakujacaInfo( const JednostkaAtakujacaInfo& obiekt )
	: Info(obiekt), atak_(obiekt.atak_), pancerz_(obiekt.pancerz_), oslona_(obiekt.oslona_),zmianaAtaku_(nullptr), zmianaPancerza_(nullptr), zmianaOslony_(nullptr)
{
	if(obiekt.zmianaAtaku_)
		zmianaAtaku_ = shared_ptr<ZmianaInterfejs>(obiekt.zmianaAtaku_->Kopia());
	if(obiekt.zmianaPancerza_)
		zmianaPancerza_ = shared_ptr<ZmianaInterfejs>(obiekt.zmianaPancerza_->Kopia());
	if(obiekt.zmianaOslony_)
		zmianaOslony_ = shared_ptr<ZmianaInterfejs>(obiekt.zmianaOslony_->Kopia());
}

JednostkaAtakujacaInfo::~JednostkaAtakujacaInfo(){
}

Obrazenia JednostkaAtakujacaInfo::pobierzAtak( const PodstawoweParametry& parametry ) const{
	if(zmianaAtaku_)
		return Obrazenia(zmianaAtaku_->policzWartosc(atak_(),static_cast<int>(parametry.pobierzPoziom()()),parametry.pobierzIdentyfikatorPlanety()()));
	else
		return atak_;
}

Obrazenia JednostkaAtakujacaInfo::pobierzPancerz( const PodstawoweParametry& parametry ) const{
	if(zmianaPancerza_)
		return Obrazenia(zmianaPancerza_->policzWartosc(pancerz_(),static_cast<int>(parametry.pobierzPoziom()()),parametry.pobierzIdentyfikatorPlanety()()));
	else
		return pancerz_;
}

Obrazenia JednostkaAtakujacaInfo::pobierzOslone(const PodstawoweParametry& parametry ) const{
	if(zmianaOslony_)
		return Obrazenia(zmianaOslony_->policzWartosc(oslona_(),static_cast<int>(parametry.pobierzPoziom()()),parametry.pobierzIdentyfikatorPlanety()()));
	else
		return oslona_;
}

string JednostkaAtakujacaInfo::napis() const{
	Logger str(NAZWAKLASY(JednostkaAtakujacaInfo));
	str.dodajKlase(Info::napis());
	str.dodajPole("Atak",atak_);
	str.dodajPole("Pancerz",pancerz_);
	str.dodajPole("Oslona",oslona_);
	if(zmianaAtaku_)
		str.dodajPole("ZmianaMasy",*zmianaAtaku_);
	if(zmianaPancerza_)
		str.dodajPole("ZmianaObjetosci",*zmianaPancerza_);
	if(zmianaOslony_)
		str.dodajPole("ZmianaPowierzchni",*zmianaOslony_);
	return str.napis();
}
