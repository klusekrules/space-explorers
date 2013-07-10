#include "Cena.h"
#include "Logger.h"
#include "Aplikacja.h"
#include "FuncTransf\ZmianaFabryka.h"
#include "XmlBO.h"
#include "Surowce.h"
#include "definicjeWezlowXML.h"

Cena::Cena( TiXmlElement* n ) throw(WyjatekParseraXML)
	: obiekty(nullptr),zmiana(nullptr)
{
	if(n!=nullptr){
		TiXmlElement* a = n->FirstChildElement(WEZEL_XML_SUROWCE);
		try{
			IdType k;
			bool ret = XmlBO::WczytajAtrybut(a,ATRYBUT_XML_IDENTYFIKATOR,k);
			obiekty= shared_ptr<Item>(Aplikacja::getInstance().getGra().getSurowce(k).TworzEgzemplarz(Ilosc(stoi(a->Attribute(ATRYBUT_XML_ILOSC),nullptr,0)),IdType()));
			zmiana = Aplikacja::getInstance().getGra().getZmianaFabryka().Tworz(XmlBO::ZnajdzWezel<NOTHROW>(n,WEZEL_XML_ZMIANA));
		}catch(exception& e){
			throw WyjatekParseraXML(EXCEPTION_PLACE,e,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}
}

Cena::Cena( const Cena& a )
{
	this->operator=(a);
}

shared_ptr<Cena::Item> Cena::PobierzKoszty(const Ilosc& i, const PodstawoweParametry& param ) const{
	shared_ptr<Item> tmp(obiekty->Kopia());
	tmp->ustawKontekst(param);
	if(zmiana){
		tmp->setIlosc(Ilosc(i()* zmiana->policzWartosc(obiekty->getIlosc()(),static_cast<int>(param.getPoziom()()),param.getIdPlanety()())));
	}else{
		tmp->setIlosc(Ilosc(i()* obiekty->getIlosc()() ));
	}
	return tmp;
}

const Cena::Item& Cena::getKoszty() const{
	return *obiekty;
}

Cena& Cena::operator=(const Cena& a){
	if(a.obiekty)
		this->obiekty=shared_ptr<Item>(a.obiekty->Kopia());
	else
		this->obiekty=nullptr;

	if(a.zmiana)
		this->zmiana=shared_ptr<ZmianaInterfejs>(a.zmiana->Kopia());
	else
		this->zmiana=nullptr;

	return *this;
}

Cena* Cena::Kopia() const{
	return new Cena(*this);
}

bool Cena::czySpelniaKoszty( const Ilosc& i, const PodstawoweParametry& p ) const{
	const Planeta& planeta = Aplikacja::getInstance().getGra().getUzytkownik().getPlaneta(p.getIdPlanety());
	
	Ilosc poz;
	if(zmiana)
		poz = Ilosc(static_cast<Ilosc::type_name>(zmiana->policzWartosc(obiekty->getIlosc()(),p.getPoziom()(),p.getIdPlanety()())));
	else
		poz = obiekty->getIlosc();

	return planeta.pobierzObiekt(obiekty->getId()).getIlosc()>=poz;
}

void Cena::setKoszty( const Item& zsKoszty ){
	obiekty = shared_ptr<Item>(zsKoszty.Kopia());
}

string Cena::toString() const{
	Logger str(CLASSNAME(Cena));
	if(obiekty.get())
		str.addField("Surowiec",*obiekty);
	if(zmiana.get())
		str.addField("Zmiana",*zmiana);
	return str.toString();
}