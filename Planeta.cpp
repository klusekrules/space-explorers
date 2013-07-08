#include "Planeta.h"
#include "Logger.h"
#include "Aplikacja.h"
#include "Utils.h"

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

IdType Planeta::dodajFlote(){
	shared_ptr< Flota > ptr = shared_ptr< Flota >(new Flota(idFloty()));
	listaFlot.insert(make_pair(ptr->getId(),ptr));
	return ptr->getId();
}

bool Planeta::przeniesDoFloty(const IdType& floty, const IdType& id, const Ilosc& ilosc){
	auto i = listaStatkow.find(id);
	if(i!=listaStatkow.end()){
		auto f = listaFlot.find(floty);
		if(f!=listaFlot.end()){
			if(ilosc <= i->second->getIlosc()){
				if(ilosc < i->second->getIlosc()){
					auto p = shared_ptr<Statek>(i->second->Podziel(ilosc));
					if(f->second->dodajStatek(p)){
						return true;
					}else{
						i->second->Polacz(*p);
						return false;
					}
				}else{
					if(f->second->dodajStatek(i->second)){
						listaStatkow.erase(i);
						listaObiektow.erase(id);
						return true;
					}else{
						return false;
					}
				}
			}
		}
	}
	return false;
}

bool Planeta::zapisz( TiXmlElement* e ) const{
	TiXmlElement* n = new TiXmlElement(CLASSNAME(Planeta));
	e->LinkEndChild( n );
	idFloty.zapisz(n);
	TiXmlElement* c = new TiXmlElement("Obiekty");
	n->LinkEndChild( c );
	for(auto o :  listaObiektow)
		if(!o.second->zapisz(c))
			return false;
	TiXmlElement* f = new TiXmlElement("Floty");
	n->LinkEndChild( f );
	for(auto o :  listaFlot)
		if(!o.second->zapisz(f))
			return false;
	return Base::zapisz(n);
}

bool Planeta::odczytaj( TiXmlElement* e ){
	if(e){
		TiXmlElement* o = e->FirstChildElement("Obiekty");
		if(o)
			for(TiXmlElement* n = o->FirstChildElement(); n != nullptr ; n = n->NextSiblingElement()){
				string c = n->Attribute("id");
				if(c.empty())
					return false;
				Utils::trim(c);
				IdType id(stoul(c,nullptr,0));
				wybuduj(id,Ilosc(0));
				auto i = listaObiektow.find(id);
				if( i == listaObiektow.end() || !i->second->odczytaj(n) )
					return false;
			}
		TiXmlElement* f = e->FirstChildElement("Floty");
		if(f)
			for(TiXmlElement* n = o->FirstChildElement(); n != nullptr ; n = n->NextSiblingElement()){
				string c = n->Attribute("id");
				if(c.empty())
					return false;
				Utils::trim(c);
				IdType id(stoul(c,nullptr,0));
				shared_ptr<Flota> ptr = shared_ptr<Flota>(new Flota (id));
				auto i = listaFlot.find(id);
				if( i != listaFlot.end() )
					return false;
				listaFlot.insert(make_pair(ptr->getId(),ptr));
			}
		return Base::odczytaj(e);
	}
	return false;
}

string Planeta::toString() const{
	Logger str(CLASSNAME(Planeta));
	str.addClass(Base::toString());
	for( auto i : listaObiektow )
		str.addField("Obiekt", *(i.second));
	return str.toString();
}
