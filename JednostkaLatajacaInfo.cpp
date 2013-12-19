#include "JednostkaLatajacaInfo.h"
#include "Logger.h"
#include "XmlBO.h"
#include "Aplikacja.h"
#include "definicjeWezlowXML.h"

JednostkaLatajacaInfo::JednostkaLatajacaInfo( const Info& info,const Klucz& klucz, const Moc& mocSilnika, const ZuzyciePaliwa& zuzyciePaliwa, const Masa& masa ) throw()
	: Info(info), rodzajNapedu_(klucz), mocSilnika_(mocSilnika), zuzyciePaliwa_(zuzyciePaliwa), masaNapedu_(masa),
	przyrostMocySilnika_(nullptr), przyrostSprawnosciSilnika_(nullptr), przyrostZuzyciaPaliwa_(nullptr), przyrostMasyNapedu_(nullptr)
{
}

JednostkaLatajacaInfo::JednostkaLatajacaInfo( tinyxml2::XMLElement* wezel ) throw(WyjatekParseraXML)
	: Info(wezel), przyrostMocySilnika_(nullptr), przyrostSprawnosciSilnika_(nullptr), przyrostZuzyciaPaliwa_(nullptr), przyrostMasyNapedu_(nullptr)
{
	if(wezel){
		try{
			Identyfikator id;
			XmlBO::WczytajAtrybut<THROW>(wezel,ATRYBUT_XML_RODZAJ_SILNIKA_ID,id);
			Poziom poziom;
			XmlBO::WczytajAtrybut<THROW>(wezel,ATRYBUT_XML_RODZAJ_SILNIKA_POZIOM,poziom);
			if( poziom <= Poziom(0) )
				throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(-1), Tekst("Nie poprawny atrybut."), Tekst("Atrybut \"poziom\" posiada niepoprawn¹ wartoœæ.") );
			rodzajNapedu_(Klucz(id,poziom)());
			
			XmlBO::WczytajAtrybut<THROW>(wezel,ATRYBUT_XML_MOC_SILNIKA,mocSilnika_);
			if( mocSilnika_ < Moc(0) )
				throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(-1), Tekst("Nie poprawny atrybut."), Tekst("Atrybut \"mocSilnika\" posiada niepoprawn¹ wartoœæ.") );
			przyrostMocySilnika_ = Utils::TworzZmiane(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel,WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,ATRYBUT_XML_MOC_SILNIKA));
			
			XmlBO::WczytajAtrybut<THROW>(wezel,ATRYBUT_XML_ZUZYCIE_PALIWA,zuzyciePaliwa_);
			if( zuzyciePaliwa_ < ZuzyciePaliwa(0) )
				throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(-1), Tekst("Nie poprawny atrybut."), Tekst("Atrybut \"zuzyciePaliwa\" posiada niepoprawn¹ wartoœæ.") );
			przyrostZuzyciaPaliwa_ = Utils::TworzZmiane(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel,WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,ATRYBUT_XML_ZUZYCIE_PALIWA));
			
			XmlBO::WczytajAtrybut<THROW>(wezel,ATRYBUT_XML_MASA_SILNIKA,masaNapedu_);
			if( masaNapedu_ < Masa(0) )
				throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(-1), Tekst("Nie poprawny atrybut."), Tekst("Atrybut \"masaNapedu\" posiada niepoprawn¹ wartoœæ.") );
			przyrostMasyNapedu_ = Utils::TworzZmiane(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel,WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,ATRYBUT_XML_MASA_SILNIKA));
			
			XmlBO::WczytajAtrybut<THROW>(wezel,ATRYBUT_XML_SPRAWNOSC_SILNIKA,sprawnoscSilnika_);
			if( sprawnoscSilnika_ < Fluktuacja(0) )
				throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(-1), Tekst("Nie poprawny atrybut."), Tekst("Atrybut \"sprawnoscSilnika\" posiada niepoprawn¹ wartoœæ.") );
			przyrostSprawnosciSilnika_ = Utils::TworzZmiane(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel,WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,ATRYBUT_XML_SPRAWNOSC_SILNIKA));
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

Moc JednostkaLatajacaInfo::pobierzMocSilnika(const PodstawoweParametry& parametry ) const{
	if(przyrostMocySilnika_)
		return Moc(przyrostMocySilnika_->policzWartosc(mocSilnika_(),static_cast<int>(parametry.pobierzPoziom()()),parametry.pobierzIdentyfikatorPlanety()()));
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
	str.dodajPole("MocSilnika",mocSilnika_);
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
