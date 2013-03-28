#include "Cena.h"
#include "Logger.h"
#include "Aplikacja.h"
#include "ZmianaFabryka.h"
#include "XmlBO.h"

Cena::Cena( ticpp::Node* n )
	: obiekty(nullptr),zmiana(nullptr)
{
	if(n!=nullptr){
		ticpp::Node* a = n->IterateChildren(CenaInterfejs::Item::LogSurowce::className(),nullptr);
		try{
			Klucz k(a);
			obiekty= shared_ptr<Item>(Aplikacja::getInstance().getSurowce(k).TworzEgzemplarz(Ilosc(stoi(a->ToElement()->GetAttribute("ilosc"),nullptr,0))));
			zmiana = ZmianaFabryka::pobierzInstancje().Tworz(XmlBO::IterateChildrenElement(n,"Zmiana",false));
		}catch(exception& e){
			throw WyjatekParseraXML(EXCEPTION_PLACE,e,WyjatekParseraXML::trescBladStrukturyXml);
		}

	}
}

Cena::Cena( const Item & zsKoszty )
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

Cena::Item Cena::PobierzKoszty() const{
	return *obiekty;
}

const Cena::Item& Cena::getKoszty() const{
	return *obiekty;
}

Cena& Cena::operator=(const Cena& a){
	this->obiekty=shared_ptr<Item>(a.obiekty->Kopia());
	return *this;
}

Cena* Cena::Kopia() const{
	return new Cena(*this);
}

bool Cena::czySpelniaWymagania( const Ilosc& i, const IdType& z ) const{
	//return (zasób na planecie) >= (i.value() * obiekty.getIlosc().value()));
	//TODO:Zimplementowanie wymaga istnienia klasy planeta z mo¿liwoœci¹ pobieranie iloœci surowców.
	return true;
}

void Cena::setKoszty( const Item& zsKoszty ){
	obiekty = shared_ptr<Item>(zsKoszty.Kopia());
}

string Cena::toString() const{
	Logger str(LogCena::className());
	if(obiekty.get())
		str.addField<Surowce>("Surowiec",*obiekty);
	if(zmiana.get())
		str.addField("Zmiana",*zmiana);
	return str.toString();
}