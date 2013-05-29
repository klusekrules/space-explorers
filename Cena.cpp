#include "Cena.h"
#include "Logger.h"
#include "Aplikacja.h"
#include "ZmianaFabryka.h"
#include "XmlBO.h"
#include "Surowce.h"

Cena::Cena( ticpp::Node* n ) throw(WyjatekParseraXML)
	: obiekty(nullptr),zmiana(nullptr)
{
	if(n!=nullptr){
		ticpp::Node* a = n->IterateChildren(CLASSNAME(Cena::Item),nullptr);
		try{
			Klucz k(a);
			obiekty= shared_ptr<Item>(Aplikacja::getInstance().getSurowce(k).TworzEgzemplarz(Ilosc(stoi(a->ToElement()->GetAttribute("ilosc"),nullptr,0))));
			zmiana = ZmianaFabryka::pobierzInstancje().Tworz(XmlBO::IterateChildrenElement(n,"Zmiana",false));
		}catch(exception& e){
			throw WyjatekParseraXML(EXCEPTION_PLACE,e,WyjatekParseraXML::trescBladStrukturyXml);
		}

	}
}

Cena::Cena( const Item & zsKoszty ) throw()
	: obiekty(zsKoszty.Kopia()) , zmiana(nullptr)
{
}

Cena::Cena( const Cena& a )
	: obiekty(a.obiekty->Kopia())
{
	zmiana = a.zmiana.get() ? shared_ptr<ZmianaInterfejs>(a.zmiana->Kopia()): nullptr;
}

Cena::~Cena()
{
}

shared_ptr<Cena::Item> Cena::PobierzKoszty(const Ilosc& i, const Poziom& p ) const{
	shared_ptr<Item> tmp(obiekty->Kopia());
	if(zmiana.get()){
		tmp->setIlosc(Ilosc(i.value()* zmiana->value(obiekty->getIlosc().value(),p)));
	}
	return tmp;
}

const Cena::Item& Cena::getKoszty() const{
	return *obiekty;
}

Cena& Cena::operator=(const Cena& a){
	if(a.obiekty!=nullptr)
		this->obiekty=shared_ptr<Item>(a.obiekty->Kopia());
	if(a.zmiana!=nullptr)
		this->zmiana=shared_ptr<ZmianaInterfejs>(a.zmiana->Kopia());
	return *this;
}

Cena* Cena::Kopia() const{
	return new Cena(*this);
}

bool Cena::czySpelniaKoszty( const Ilosc& i, const Poziom& p, const IdType& idPlanety ) const{
	//return (zasób na planecie) >= (i.value() * obiekty.getIlosc().value()));
	//TODO:Zimplementowanie wymaga istnienia klasy planeta z mo¿liwoœci¹ pobieranie iloœci surowców.
	return true;
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