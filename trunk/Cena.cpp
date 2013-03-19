#include "Cena.h"
#include "Logger.h"
#include "Aplikacja.h"

Cena::Cena( ticpp::Node* n )
	: obiekty(nullptr)
{
	if(n!=nullptr){
		ticpp::Node* a = n->IterateChildren(CenaInterfejs::Item::LogSurowce::className(),nullptr);
		try{
			Klucz k(a);
			obiekty= Aplikacja::getInstance().getSurowce(k).TworzEgzemplarz(Ilosc(stoi(n->ToElement()->GetAttribute("ilosc"))));
		}catch(exception& e){
			throw WyjatekParseraXML(EXCEPTION_PLACE,e,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}
}

Cena::Cena( const Item & zsKoszty )
	: obiekty(zsKoszty.Kopia())
{
}

Cena::Cena( const Cena& a )
	: obiekty(a.obiekty->Kopia())
{
}

Cena::~Cena()
{
	if(obiekty)
		delete obiekty;
}

Cena::Item Cena::PobierzKoszty() const{
	return *obiekty;
}

const Cena::Item& Cena::getKoszty() const{
	return *obiekty;
}

Cena& Cena::operator=(const Cena& a){
	if(obiekty)
		delete obiekty;
	this->obiekty=a.obiekty->Kopia();
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
	obiekty = zsKoszty.Kopia();
}

string Cena::toString() const{
	Logger str(LogCena::className());
	str.addField<Surowce>("Surowiec",*obiekty);
	return str.toString();
}