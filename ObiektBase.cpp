#include "ObiektBase.h"
#include "ObiektBaseInfo.h"
#include "Logger.h"
#include "Utils.h"
#include "DefinicjeWezlowXML.h"

ObiektBase::ObiektBase( const Ilosc& i, const Poziom& p, const Identyfikator& idP, const ObiektBaseInfo& iInfo) throw()
	: PodstawoweParametry(p,idP), Bazowa(iInfo), ilosc(i), obiektBaseInfo(iInfo)
{
}

ObiektBase::ObiektBase( const Ilosc& i, const PodstawoweParametry& p, const ObiektBaseInfo& iInfo) throw()
	: PodstawoweParametry(p), Bazowa(iInfo), ilosc(i), obiektBaseInfo(iInfo)
{
}

Czas ObiektBase::pobierzCzasRozbudowy( )const{
	PodstawoweParametry param(*this);
	param.wzrostPoziomu();
	return obiektBaseInfo.pobierzCzasBudowy(ilosc,param);
}

ObiektBase* ObiektBase::Kopia() const{
	return new ObiektBase(*this);
}

ObiektBase* ObiektBase::Podziel( const Ilosc& i ){
	if( czyMoznaPodzielic(i) ){
		ilosc-=i;
		return new ObiektBase( i, getPoziom(), getIdPlanety() , obiektBaseInfo );
	}
	return nullptr;
}

bool ObiektBase::Polacz( ObiektBase& obj ){
	if(czyMoznaPolaczyc(obj)){
		ilosc+=obj.getIlosc();
		return true;
	}else{
		return false;
	}
}

void ObiektBase::wybuduj(const Ilosc& i){
	ilosc += i;
}
		
Klucz ObiektBase::ID() const{
	return Klucz( pobierzIdentyfikator() , getPoziom() );
}


bool ObiektBase::czyMoznaPolaczyc( const ObiektBase& objBase )const{
	return typeid(*this) == typeid(objBase) && objBase.pobierzIdentyfikator() == pobierzIdentyfikator() && objBase.getPoziom() == getPoziom();
}

bool ObiektBase::czyMoznaPodzielic( const Ilosc& i ) const{
	return ilosc>i;
}

const Ilosc& ObiektBase::getIlosc() const{
	return ilosc;
}

void ObiektBase::setIlosc( const Ilosc& i ){
	ilosc = i;
}

Wymagania::PrzetworzonaCena ObiektBase::PobierzKoszty() const{
	return obiektBaseInfo.PobierzKoszty(getIlosc(),*this);
}


Wymagania::PrzetworzoneWymogi ObiektBase::PobierzWarunki()const{
	return obiektBaseInfo.listaWarunkow(*this);
}

bool ObiektBase::czyMoznaWybudowac()const{
	return obiektBaseInfo.czySpelniaWymagania(ilosc,*this);
}

const ObiektBaseInfo& ObiektBase::getObiektBaseInfo()const{
	return obiektBaseInfo;
}

bool ObiektBase::zapisz( TiXmlElement* e ) const {
	e->SetAttribute(ATRYBUT_XML_ILOSC,ilosc.napis());
	return PodstawoweParametry::zapisz(e) && Bazowa::zapisz(e);
}

bool ObiektBase::odczytaj( TiXmlElement* e ){
	if(e){
		auto ptr = e->Attribute(ATRYBUT_XML_ILOSC);
		if(!ptr)
			return false;
		string c = ptr;
		Utils::trim(c);
		if(c.empty())
			return false;
		ilosc(stold(c));
		return Bazowa::odczytaj(e) && PodstawoweParametry::odczytaj(e);
	}
	return false;
}

string ObiektBase::napis() const{
	Logger str(NAZWAKLASY(ObiektBase));
	str.dodajKlase(Bazowa::napis());
	str.dodajKlase(PodstawoweParametry::napis());
	str.dodajPole(NAZWAKLASY(Ilosc),ilosc);
	str.dodajPole(NAZWAKLASY(ObiektBaseInfo)+"ID",obiektBaseInfo.pobierzIdentyfikator());
	return str.napis();
}
