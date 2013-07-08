#include "Planeta.h"
#include "Logger.h"
#include "Aplikacja.h"

Planeta::Planeta(const IdType& id)
	: Base(id), wlasciciel(nullptr),
	pustyobiekBaseInfo( Info(Tekst(""),Tekst(""),IdType(0),Wymagania(nullptr)) , Poziom(0) ), 
	pustyObiektBase( Ilosc(0), Poziom(0),IdType(0), pustyobiekBaseInfo )
{
}

Planeta::~Planeta(void)
{
}

void Planeta::ustawWlasciciela( Uzytkownik* w ){
	wlasciciel=w;
}

Uzytkownik* Planeta::pobierzWlasciciela( void ) const{
	return wlasciciel;
}

Ilosc Planeta::pobierzIloscTypowObiektow()const{
	if(listaObiektow.size() != listaBudynkow.size()+listaStatkow.size()+listaSurowcow.size()+listaTechnologii.size())
		throw NiepoprawnaIloscObiektow(EXCEPTION_PLACE,Ilosc(listaObiektow.size()));
	return Ilosc(listaObiektow.size()); 
}

const ObiektBase& Planeta::pobierzObiekt(const IdType& id) const{
	auto i = listaObiektow.find(id);
	if(i!=listaObiektow.end())
		return *(i->second);
	return pustyObiektBase;
}

bool Planeta::dodajObiekt( shared_ptr< Budynek > ptr ){
	auto i = listaObiektow.find(ptr->getId());
	if(i!=listaObiektow.end())
		return false;
	listaBudynkow.insert(make_pair(ptr->getId(),ptr));
	listaObiektow.insert(make_pair(ptr->getId(),ptr));
	return true;
}

bool Planeta::dodajObiekt( shared_ptr< Statek > ptr ){
	auto i = listaObiektow.find(ptr->getId());
	if(i!=listaObiektow.end())
		return false;
	listaStatkow.insert(make_pair(ptr->getId(),ptr));
	listaObiektow.insert(make_pair(ptr->getId(),ptr));
	return true;
}

bool Planeta::dodajObiekt( shared_ptr< Technologia > ptr ){
	auto i = listaObiektow.find(ptr->getId());
	if(i!=listaObiektow.end())
		return false;
	listaTechnologii.insert(make_pair(ptr->getId(),ptr));
	listaObiektow.insert(make_pair(ptr->getId(),ptr));
	return true;
}

bool Planeta::dodajObiekt( shared_ptr< Surowce > ptr ){
	auto i = listaObiektow.find(ptr->getId());
	if(i!=listaObiektow.end())
		return false;
	listaSurowcow.insert(make_pair(ptr->getId(),ptr));
	listaObiektow.insert(make_pair(ptr->getId(),ptr));
	return true;
}

bool Planeta::wybuduj( const IdType& id, const Ilosc& ilosc ){
	auto i = listaObiektow.find(id);
	if(i!=listaObiektow.end()){
		i->second->wybuduj(ilosc);
		return true;
	}else{
		return Aplikacja::getInstance().getGra().wybudujNaPlanecie(*this,id,ilosc);
	}
}

bool Planeta::zapisz( TiXmlElement* e ) const{
	TiXmlElement* n = new TiXmlElement(CLASSNAME(Planeta));
	e->LinkEndChild( n );
	for(auto o :  listaObiektow)
		if(!o.second->zapisz(n))
			return false;
	return Base::zapisz(n);
}

bool Planeta::odczytaj( TiXmlElement* n ){

	return false;
}

string Planeta::toString() const{
	Logger str(CLASSNAME(Planeta));
	str.addClass(Base::toString());
	for( auto i : listaObiektow )
		str.addField("Obiekt", *(i.second));
	return str.toString();
}
