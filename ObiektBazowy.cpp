#include "ObiektBazowy.h"
#include "ObiektBazowyInfo.h"
#include "Logger.h"
#include "Utils.h"
#include "DefinicjeWezlowXML.h"
#include "XmlBO.h"

ObiektBazowy::ObiektBazowy( const Ilosc& ilosc, const Poziom& poziom, const Identyfikator& identyfikatorPlanety, const ObiektBazowyInfo& obiektBazowyInfo) throw()
	: PodstawoweParametry(poziom,identyfikatorPlanety), Bazowa(obiektBazowyInfo), ilosc_(ilosc), obiektBazowyInfo_(obiektBazowyInfo)
{
}

ObiektBazowy::ObiektBazowy( const Ilosc& ilosc, const PodstawoweParametry& parametryPodstawowe, const ObiektBazowyInfo& obiektBazowyInfo) throw()
	: PodstawoweParametry(parametryPodstawowe), Bazowa(obiektBazowyInfo), ilosc_(ilosc), obiektBazowyInfo_(obiektBazowyInfo)
{
}

Czas ObiektBazowy::pobierzCzasRozbudowy( )const{
	PodstawoweParametry param(*this);
	param.wzrostPoziomu();
	return obiektBazowyInfo_.pobierzCzasBudowy(pobierzIlosc(),param);
}

ObiektBazowy* ObiektBazowy::kopia() const{
	return new ObiektBazowy(*this);
}

ObiektBazowy* ObiektBazowy::podziel( const Ilosc& ilosc ){
	if( czyMoznaPodzielic(ilosc) ){
		ilosc_-=ilosc;
		return new ObiektBazowy( ilosc, pobierzPoziom(), pobierzIdentyfikatorPlanety() , obiektBazowyInfo_ );
	}
	return nullptr;
}

bool ObiektBazowy::polacz( const ObiektBazowy& obiektBazowy ){
	if(czyMoznaPolaczyc(obiektBazowy)){
		ilosc_+=obiektBazowy.pobierzIlosc();
		return true;
	}else{
		return false;
	}
}

void ObiektBazowy::wybuduj( const Ilosc& ilosc ){
	ilosc_ += ilosc;
}

Klucz ObiektBazowy::ID() const{
	return Klucz( pobierzIdentyfikator() , pobierzPoziom() );
}


bool ObiektBazowy::czyMoznaPolaczyc( const ObiektBazowy& obiektBazowy )const{
	return typeid(*this) == typeid(obiektBazowy) && obiektBazowy.pobierzIdentyfikator() == pobierzIdentyfikator() && obiektBazowy.pobierzPoziom() == pobierzPoziom();
}

bool ObiektBazowy::czyMoznaPodzielic( const Ilosc& ilosc ) const{
	return ilosc_>ilosc;
}

const Ilosc& ObiektBazowy::pobierzIlosc() const{
	return ilosc_;
}

void ObiektBazowy::ustawIlosc( const Ilosc& ilosc ){
	ilosc_ = ilosc;
}

Wymagania::PrzetworzonaCena ObiektBazowy::pobierzKosztyRozbudowy() const{
	PodstawoweParametry param(*this);
	param.wzrostPoziomu();
	return obiektBazowyInfo_.pobierzKoszty(pobierzIlosc(),param);
}

Wymagania::PrzetworzoneWymogi ObiektBazowy::pobierzWarunkiRozbudowy()const{
	PodstawoweParametry param(*this);
	param.wzrostPoziomu();
	return obiektBazowyInfo_.pobierzWymogi(param);
}

bool ObiektBazowy::czyMoznaRozbudowac()const{
	PodstawoweParametry param(*this);
	param.wzrostPoziomu();
	return obiektBazowyInfo_.czySpelniaWymagania(pobierzIlosc(),param);
}

const ObiektBazowyInfo& ObiektBazowy::getObiektBaseInfo()const{
	return obiektBazowyInfo_;
}

bool ObiektBazowy::zapisz( TiXmlElement* wezel ) const {
	wezel->SetAttribute(ATRYBUT_XML_ILOSC,pobierzIlosc().napis());
	return PodstawoweParametry::zapisz(wezel) && Bazowa::zapisz(wezel);
}

bool ObiektBazowy::odczytaj( TiXmlElement* wezel ){
	if(wezel){
		if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_ILOSC,ilosc_))
			return false;
		return Bazowa::odczytaj(wezel) && PodstawoweParametry::odczytaj(wezel);
	}
	return false;
}

string ObiektBazowy::napis() const{
	Logger str(NAZWAKLASY(ObiektBazowy));
	str.dodajKlase(Bazowa::napis());
	str.dodajKlase(PodstawoweParametry::napis());
	str.dodajPole(NAZWAKLASY(Ilosc),ilosc_);
	str.dodajPole(NAZWAKLASY(ObiektBazowyInfo)+"ID",obiektBazowyInfo_.pobierzIdentyfikator());
	return str.napis();
}
