#include "ObiektInfo.h"
#include "Logger.h"
#include "XmlBO.h"
#include "Aplikacja.h"
#include "definicjeWezlowXML.h"

ObiektInfo::ObiektInfo( const Masa& masa, const Objetosc& objetosc, const Powierzchnia& powierzchnia, const ObiektBazowyInfo& obiektBazowyInfo ) throw()
	: ObiektBazowyInfo(obiektBazowyInfo),powierzchnia_(powierzchnia), zmianaPowierzchni_(nullptr),
	objetosc_(objetosc), zmianaObjetosci_(nullptr), masa_(masa), zmianaMasy_(nullptr)
{
}

ObiektInfo::ObiektInfo( tinyxml2::XMLElement* wezel ) throw(WyjatekParseraXML)
	: ObiektBazowyInfo(wezel), zmianaPowierzchni_(nullptr), zmianaObjetosci_(nullptr), zmianaMasy_(nullptr)
{
	if(wezel){
		try{
			XmlBO::WczytajAtrybut<THROW>(wezel,ATRYBUT_XML_MASA,masa_);
			if( masa_ < Masa(0) )
				throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(-1), Tekst("Nie poprawny atrybut."), Tekst("Atrybut \"masa\" posiada niepoprawną wartość.") );
			zmianaMasy_ = Utils::TworzZmiane(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel,WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,ATRYBUT_XML_MASA));
			
			XmlBO::WczytajAtrybut<THROW>(wezel,ATRYBUT_XML_OBJETOSC,objetosc_);
			if( objetosc_ < Objetosc(0) )
				throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(-1), Tekst("Nie poprawny atrybut."), Tekst("Atrybut \"objetosc\" posiada niepoprawną wartość.") );
			zmianaObjetosci_ = Utils::TworzZmiane(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel,WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,ATRYBUT_XML_OBJETOSC));
			
			XmlBO::WczytajAtrybut<THROW>(wezel,ATRYBUT_XML_POWIERZCHNIA,powierzchnia_);
			if( powierzchnia_ < Powierzchnia(0) )
				throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(-1), Tekst("Nie poprawny atrybut."), Tekst("Atrybut \"powierzchnia\" posiada niepoprawną wartość.") );
			zmianaPowierzchni_ = Utils::TworzZmiane(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel,WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,ATRYBUT_XML_POWIERZCHNIA));
		}catch(exception& wyjatek){
			throw WyjatekParseraXML(EXCEPTION_PLACE,wyjatek,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}
}

ObiektInfo::~ObiektInfo(){
}

Powierzchnia ObiektInfo::pobierzPowierzchnie(const Poziom& poziom, const Identyfikator& identyfikatorPlanety) const {
	if(zmianaPowierzchni_ == nullptr)
		return powierzchnia_;			
	return Powierzchnia(zmianaPowierzchni_->policzWartosc(powierzchnia_(),static_cast<int>(poziom()),identyfikatorPlanety()));
}

Objetosc ObiektInfo::pobierzObjetosc(const Poziom& poziom, const Identyfikator& identyfikatorPlanety) const {
	if(zmianaObjetosci_ == nullptr)
		return objetosc_;
	return Objetosc(zmianaObjetosci_->policzWartosc(objetosc_(),static_cast<int>(poziom()), identyfikatorPlanety()));
}

Masa ObiektInfo::pobierzMase(const Poziom& poziom, const Identyfikator& identyfikatorPlanety) const {
	if(zmianaMasy_ == nullptr)
		return masa_;
	return Masa(zmianaMasy_->policzWartosc(masa_(),static_cast<int>(poziom()), identyfikatorPlanety()));
}

Obiekt* ObiektInfo::tworzEgzemplarz( const Ilosc& ilosc, const Identyfikator& identyfikatorPlanety ) const {
	return new Obiekt( ilosc, pobierzPoziom(),identyfikatorPlanety, *this );
}

string ObiektInfo::napis() const{
	Logger str(NAZWAKLASY(ObiektInfo));
	str.dodajKlase(ObiektBazowyInfo::napis());
	str.dodajPole(NAZWAKLASY(Masa),masa_);
	str.dodajPole(NAZWAKLASY(Objetosc),objetosc_);
	str.dodajPole(NAZWAKLASY(Powierzchnia),powierzchnia_);
	if(zmianaMasy_!=nullptr)
		str.dodajPole("ZmianaMasy",*zmianaMasy_);
	if(zmianaObjetosci_!=nullptr)
		str.dodajPole("ZmianaObjetosci",*zmianaObjetosci_);
	if(zmianaPowierzchni_!=nullptr)
		str.dodajPole("ZmianaPowierzchni",*zmianaPowierzchni_);
	return str.napis();
}
