#include "ObiektBazowy.h"
#include "ObiektBaseInfo.h"
#include "Logger.h"
#include "Utils.h"
#include "DefinicjeWezlowXML.h"

ObiektBazowy::ObiektBazowy( const Ilosc& ilosc, const Poziom& poziom, const Identyfikator& identyfikatorPlanety, const ObiektBaseInfo& obiektBazowyInfo) throw()
	: PodstawoweParametry(poziom,identyfikatorPlanety), Bazowa(obiektBazowyInfo), ilosc_(ilosc), obiektBazowyInfo_(obiektBazowyInfo)
{
}

ObiektBazowy::ObiektBazowy( const Ilosc& ilosc, const PodstawoweParametry& parametryPodstawowe, const ObiektBaseInfo& obiektBazowyInfo) throw()
	: PodstawoweParametry(parametryPodstawowe), Bazowa(obiektBazowyInfo), ilosc_(ilosc), obiektBazowyInfo_(obiektBazowyInfo)
{
}

Czas ObiektBazowy::pobierzCzasRozbudowy( )const{
	PodstawoweParametry param(*this);
	param.wzrostPoziomu();
	return obiektBazowyInfo_.pobierzCzasBudowy(ilosc_,param);
}

ObiektBazowy* ObiektBazowy::Kopia() const{
	return new ObiektBazowy(*this);
}

ObiektBazowy* ObiektBazowy::Podziel( const Ilosc& ilosc ){
	if( czyMoznaPodzielic(ilosc) ){
		ilosc_-=ilosc;
		return new ObiektBazowy( ilosc, pobierzPoziom(), pobierzIdentyfikatorPlanety() , obiektBazowyInfo_ );
	}
	return nullptr;
}

bool ObiektBazowy::Polacz( const ObiektBazowy& obiektBazowy ){
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

Wymagania::PrzetworzonaCena ObiektBazowy::PobierzKoszty() const{
	return obiektBazowyInfo_.PobierzKoszty(pobierzIlosc(),*this);
}


Wymagania::PrzetworzoneWymogi ObiektBazowy::PobierzWarunki()const{
	return obiektBazowyInfo_.listaWarunkow(*this);
}

bool ObiektBazowy::czyMoznaWybudowac()const{
	return obiektBazowyInfo_.czySpelniaWymagania(pobierzIlosc(),*this);
}

const ObiektBaseInfo& ObiektBazowy::getObiektBaseInfo()const{
	return obiektBazowyInfo_;
}

bool ObiektBazowy::zapisz( TiXmlElement* wezel ) const {
	wezel->SetAttribute(ATRYBUT_XML_ILOSC,ilosc_.napis());
	return PodstawoweParametry::zapisz(wezel) && Bazowa::zapisz(wezel);
}

bool ObiektBazowy::odczytaj( TiXmlElement* wezel ){
	if(wezel){
		auto atrybut = wezel->Attribute(ATRYBUT_XML_ILOSC);
		if(!atrybut)
			return false;
		string napisAtrybutu = atrybut;
		Utils::trim(napisAtrybutu);
		if(napisAtrybutu.empty())
			return false;
		ilosc_(stold(napisAtrybutu));
		return Bazowa::odczytaj(wezel) && PodstawoweParametry::odczytaj(wezel);
	}
	return false;
}

string ObiektBazowy::napis() const{
	Logger str(NAZWAKLASY(ObiektBazowy));
	str.dodajKlase(Bazowa::napis());
	str.dodajKlase(PodstawoweParametry::napis());
	str.dodajPole(NAZWAKLASY(Ilosc),ilosc_);
	str.dodajPole(NAZWAKLASY(ObiektBaseInfo)+"ID",obiektBazowyInfo_.pobierzIdentyfikator());
	return str.napis();
}
