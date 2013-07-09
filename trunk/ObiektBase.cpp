#include "ObiektBase.h"
#include "ObiektBaseInfo.h"
#include "Logger.h"
#include "Utils.h"
#include "DefinicjeWezlowXML.h"

ObiektBase::ObiektBase( const Ilosc& i, const Poziom& p, const IdType& idP, const ObiektBaseInfo& iInfo) throw()
	: PodstawoweParametry(p,idP), Base(iInfo), ilosc(i), obiektBaseInfo(iInfo)
{
}

ObiektBase::ObiektBase( const Ilosc& i, const PodstawoweParametry& p, const ObiektBaseInfo& iInfo) throw()
	: PodstawoweParametry(p), Base(iInfo), ilosc(i), obiektBaseInfo(iInfo)
{
}

Czas ObiektBase::pobierzCzasBudowy( )const{
	return Czas(obiektBaseInfo.pobierzCzasBudowy(*this)()*ilosc());
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
	return Klucz( getId() , getPoziom() );
}


bool ObiektBase::czyMoznaPolaczyc( const ObiektBase& objBase )const{
	return typeid(*this) == typeid(objBase) && objBase.getId() == getId() && objBase.getPoziom() == getPoziom();
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

Cennik::ListaSurowcow ObiektBase::PobierzKoszty() const{
	return obiektBaseInfo.PobierzKoszty(getIlosc(),*this);
}


Warunek::PrzetworzoneWarunki ObiektBase::PobierzWarunki()const{
	return obiektBaseInfo.listaWarunkow(*this);
}

bool ObiektBase::czyMoznaWybudowac()const{
	return obiektBaseInfo.czySpelniaWymagania(ilosc,*this);
}

const ObiektBaseInfo& ObiektBase::getObiektBaseInfo()const{
	return obiektBaseInfo;
}

bool ObiektBase::zapisz( TiXmlElement* e ) const {
	e->SetAttribute(ATRYBUT_XML_ILOSC,ilosc.toString());
	return PodstawoweParametry::zapisz(e) && Base::zapisz(e);
}

bool ObiektBase::odczytaj( TiXmlElement* e ){
	if(e){
		string c = e->Attribute(ATRYBUT_XML_ILOSC);
		if(c.empty())
			return false;
		Utils::trim(c);
		ilosc.setIlosc(stold(c));
		return PodstawoweParametry::odczytaj(e) && Base::odczytaj(e);
	}
	return false;
}

string ObiektBase::toString() const{
	Logger str(CLASSNAME(ObiektBase));
	str.addClass(Base::toString());
	str.addClass(PodstawoweParametry::toString());
	str.addField(CLASSNAME(Ilosc),ilosc);
	str.addField(CLASSNAME(ObiektBaseInfo)+"ID",obiektBaseInfo.getId());
	return str.toString();
}
