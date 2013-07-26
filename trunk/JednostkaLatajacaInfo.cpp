#include "JednostkaLatajacaInfo.h"
#include "Logger.h"
#include "XmlBO.h"
#include "Aplikacja.h"
#include "definicjeWezlowXML.h"

JednostkaLatajacaInfo::JednostkaLatajacaInfo( const Info& info,const Klucz& klucz, const MocSilnika& mocSilnika, const ZuzyciePaliwa& zuzyciePaliwa, const Masa& masa ) throw()
	: Info(info), rodzajNapedu_(klucz), mocSilnika_(mocSilnika), zuzyciePaliwa_(zuzyciePaliwa), masaNapedu_(masa),
	przyrostMocySilnika_(nullptr), przyrostSprawnosciSilnika_(nullptr), przyrostZuzyciaPaliwa_(nullptr), przyrostMasyNapedu_(nullptr)
{
}

JednostkaLatajacaInfo::JednostkaLatajacaInfo( TiXmlElement* wezel ) throw(WyjatekParseraXML)
	: Info(wezel), przyrostMocySilnika_(nullptr), przyrostSprawnosciSilnika_(nullptr), przyrostZuzyciaPaliwa_(nullptr), przyrostMasyNapedu_(nullptr)
{
	if(wezel){
		try{
			ZmianaFabryka& fabryka = Aplikacja::pobierzInstancje().pobierzGre().pobierzFabrykeZmian();
			Identyfikator id;
			XmlBO::WczytajAtrybut<THROW>(wezel,ATRYBUT_XML_RODZAJ_SILNIKA_ID,id);
			Poziom poziom;
			XmlBO::WczytajAtrybut<THROW>(wezel,ATRYBUT_XML_RODZAJ_SILNIKA_POZIOM,poziom);
			rodzajNapedu_(Klucz(id,poziom)());
			
			XmlBO::WczytajAtrybut<THROW>(wezel,ATRYBUT_XML_MOC_SILNIKA,mocSilnika_);
			przyrostMocySilnika_ = fabryka.Tworz(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel,WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,ATRYBUT_XML_MOC_SILNIKA));
			
			XmlBO::WczytajAtrybut<THROW>(wezel,ATRYBUT_XML_ZUZYCIE_PALIWA,zuzyciePaliwa_);
			przyrostZuzyciaPaliwa_ = fabryka.Tworz(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel,WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,ATRYBUT_XML_ZUZYCIE_PALIWA));
			
			XmlBO::WczytajAtrybut<THROW>(wezel,ATRYBUT_XML_MASA_SILNIKA,masaNapedu_);
			przyrostMasyNapedu_ = fabryka.Tworz(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel,WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,ATRYBUT_XML_MASA_SILNIKA));
			
			XmlBO::WczytajAtrybut<THROW>(wezel,ATRYBUT_XML_SPRAWNOSC_SILNIKA,sprawnoscSilnika_);
			przyrostSprawnosciSilnika_ = fabryka.Tworz(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel,WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,ATRYBUT_XML_SPRAWNOSC_SILNIKA));
		}catch(exception& wyjatek){
			throw WyjatekParseraXML(EXCEPTION_PLACE,wyjatek,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}
}

JednostkaLatajacaInfo::JednostkaLatajacaInfo( const JednostkaLatajacaInfo& obiekt)
	: Info(obiekt), przyrostMocySilnika_(nullptr), przyrostSprawnosciSilnika_(nullptr), przyrostZuzyciaPaliwa_(nullptr), przyrostMasyNapedu_(nullptr),
	rodzajNapedu_(obiekt.rodzajNapedu_), mocSilnika_(obiekt.mocSilnika_), zuzyciePaliwa_(obiekt.zuzyciePaliwa_), masaNapedu_(obiekt.masaNapedu_)
{
	if(obiekt.przyrostMasyNapedu_)
		przyrostMasyNapedu_ = shared_ptr<ZmianaInterfejs>( obiekt.przyrostMasyNapedu_->Kopia());

	if(obiekt.przyrostSprawnosciSilnika_)
		przyrostSprawnosciSilnika_ = shared_ptr<ZmianaInterfejs>( obiekt.przyrostSprawnosciSilnika_->Kopia());

	if(obiekt.przyrostZuzyciaPaliwa_)
		przyrostZuzyciaPaliwa_ = shared_ptr<ZmianaInterfejs>( obiekt.przyrostZuzyciaPaliwa_->Kopia());

	if(obiekt.przyrostMocySilnika_)
		przyrostMocySilnika_ = shared_ptr<ZmianaInterfejs>( obiekt.przyrostMocySilnika_->Kopia());
}

JednostkaLatajacaInfo::~JednostkaLatajacaInfo(){
}

const Klucz& JednostkaLatajacaInfo::pobierzRodzajNapedu() const{
	return rodzajNapedu_;
}

MocSilnika JednostkaLatajacaInfo::pobierzMocSilnika(const PodstawoweParametry& parametry ) const{
	if(przyrostMocySilnika_)
		return MocSilnika(przyrostMocySilnika_->policzWartosc(mocSilnika_(),static_cast<int>(parametry.pobierzPoziom()()),parametry.pobierzIdentyfikatorPlanety()()));
	else
		return mocSilnika_;
}

ZuzyciePaliwa JednostkaLatajacaInfo::pobierzZuzyciePaliwa(const PodstawoweParametry& parametry ) const{
	if(przyrostZuzyciaPaliwa_)
		return ZuzyciePaliwa(przyrostZuzyciaPaliwa_->policzWartosc(zuzyciePaliwa_(),static_cast<int>(parametry.pobierzPoziom()()),parametry.pobierzIdentyfikatorPlanety()()));
	else
		return zuzyciePaliwa_;
}

Masa JednostkaLatajacaInfo::pobierzMasaNapedu( const PodstawoweParametry& parametry ) const{
	if(przyrostMasyNapedu_)
		return Masa(przyrostMasyNapedu_->policzWartosc(masaNapedu_(),static_cast<int>(parametry.pobierzPoziom()()),parametry.pobierzIdentyfikatorPlanety()()));
	else
		return masaNapedu_;
}

Fluktuacja JednostkaLatajacaInfo::pobierzSprawnoscSilnika( const PodstawoweParametry& parametry ) const{
	if(przyrostSprawnosciSilnika_)
		return Fluktuacja(static_cast<float>(przyrostSprawnosciSilnika_->policzWartosc(sprawnoscSilnika_(),static_cast<int>(parametry.pobierzPoziom()()),parametry.pobierzIdentyfikatorPlanety()())));
	else
		return sprawnoscSilnika_;
}

string JednostkaLatajacaInfo::napis() const{
	Logger str(NAZWAKLASY(JednostkaLatajacaInfo));
	str.dodajKlase(Info::napis());
	str.dodajPole("RodzajNapedu",rodzajNapedu_);
	str.dodajPole(NAZWAKLASY(MocSilnika),mocSilnika_);
	if(przyrostMocySilnika_){
		str.dodajPole("ZmianaMocySilnika",*przyrostMocySilnika_);
	}
	str.dodajPole("SprawnoscSilnika",sprawnoscSilnika_);
	if(przyrostSprawnosciSilnika_){
		str.dodajPole("ZmianaSprawnosciSilnika",*przyrostSprawnosciSilnika_);
	}
	str.dodajPole(NAZWAKLASY(ZuzyciePaliwa),zuzyciePaliwa_);
	if(przyrostZuzyciaPaliwa_){
		str.dodajPole("ZmianaZuzyciaPaliwa",*przyrostZuzyciaPaliwa_);
	}
	str.dodajPole("MasaNapedu",masaNapedu_);
	if(przyrostMasyNapedu_){
		str.dodajPole("ZmianaMasyNapedu",*przyrostMasyNapedu_);
	}
	return str.napis();
}
