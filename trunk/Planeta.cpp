#include "Planeta.h"
#include "Logger.h"
#include "Aplikacja.h"
#include "Utils.h"
#include "DefinicjeWezlowXML.h"
#include "XmlBO.h"

Planeta::Planeta(const Identyfikator& id)
	: Bazowa(id), wlasciciel(nullptr),
	pustyobiekBaseInfo( Info(Tekst(""),Tekst(""),Identyfikator(0),Wymagania(nullptr)) , Poziom(0) )
{
	pustyObiektBase = shared_ptr<ObiektBazowy>(new ObiektBazowy( Ilosc(0), Poziom(0),Identyfikator(0), pustyobiekBaseInfo ));
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

const ObiektBazowy& Planeta::pobierzObiekt(const Identyfikator& id) const{
	auto i = listaObiektow.find(id);
	if(i!=listaObiektow.end())
		return *(i->second);
	return *pustyObiektBase;
}

const Statek& Planeta::pobierzStatek(const Identyfikator& id) const{
	auto i = listaStatkow.find(id);
	if(i!=listaStatkow.end())
		return *(i->second);
	throw NieznalezionoObiektu(EXCEPTION_PLACE,id.napis());
}

const Technologia& Planeta::pobierzTechnologie(const Identyfikator& id) const{
	auto i = listaTechnologii.find(id);
	if(i!=listaTechnologii.end())
		return *(i->second);
	throw NieznalezionoObiektu(EXCEPTION_PLACE,id.napis());
}

const Budynek& Planeta::pobierzBudynek(const Identyfikator& id) const{
	auto i = listaBudynkow.find(id);
	if(i!=listaBudynkow.end())
		return *(i->second);
	throw NieznalezionoObiektu(EXCEPTION_PLACE,id.napis());
}

bool Planeta::dodajObiekt( shared_ptr< Budynek > ptr ){
	auto i = listaObiektow.find(ptr->pobierzIdentyfikator());
	if(i!=listaObiektow.end())
		return false;
	listaBudynkow.insert(make_pair(ptr->pobierzIdentyfikator(),ptr));
	listaObiektow.insert(make_pair(ptr->pobierzIdentyfikator(),ptr));
	return true;
}

bool Planeta::dodajObiekt( shared_ptr< Statek > ptr ){
	auto i = listaObiektow.find(ptr->pobierzIdentyfikator());
	if(i!=listaObiektow.end())
		return false;
	listaStatkow.insert(make_pair(ptr->pobierzIdentyfikator(),ptr));
	listaObiektowZaladunkowych.insert(make_pair(ptr->pobierzIdentyfikator(),ptr));
	listaObiektow.insert(make_pair(ptr->pobierzIdentyfikator(),ptr));
	return true;
}

bool Planeta::dodajObiekt( shared_ptr< Technologia > ptr ){
	auto i = listaObiektow.find(ptr->pobierzIdentyfikator());
	if(i!=listaObiektow.end())
		return false;
	listaTechnologii.insert(make_pair(ptr->pobierzIdentyfikator(),ptr));
	listaObiektow.insert(make_pair(ptr->pobierzIdentyfikator(),ptr));
	return true;
}

bool Planeta::dodajObiekt( shared_ptr< Surowce > ptr ){
	auto i = listaObiektow.find(ptr->pobierzIdentyfikator());
	if(i!=listaObiektow.end())
		return false;
	listaSurowcow.insert(make_pair(ptr->pobierzIdentyfikator(),ptr));
	listaObiektowZaladunkowych.insert(make_pair(ptr->pobierzIdentyfikator(),ptr));
	listaObiektow.insert(make_pair(ptr->pobierzIdentyfikator(),ptr));
	return true;
}

bool Planeta::wybuduj( const Identyfikator& id, const Ilosc& ilosc ){
	auto i = listaObiektow.find(id);
	if(i!=listaObiektow.end()){
		i->second->wybuduj(ilosc);
		return true;
	}else{
		return Aplikacja::getInstance().getGra().wybudujNaPlanecie(*this,id,ilosc);
	}
}

void Planeta::wybuduj( shared_ptr< ObiektBazowy > obiekt ){
	auto i = listaObiektow.find(obiekt->pobierzIdentyfikator());
	if(i!=listaObiektow.end()){
		i->second->wybuduj(obiekt->pobierzIlosc());
	}else{
		Aplikacja::getInstance().getGra().wybudujNaPlanecie(*this,obiekt->pobierzObiektBaseInfo(),obiekt->pobierzIlosc());
	}
}

Identyfikator Planeta::dodajFlote(){
	shared_ptr< Flota > ptr = shared_ptr< Flota >(new Flota(Identyfikator(idFloty()),Identyfikator(),Identyfikator(),Flota::CelPodrozy::Transport));
	listaFlot.insert(make_pair(ptr->pobierzIdentyfikator(),ptr));
	return ptr->pobierzIdentyfikator();
}

bool Planeta::przeniesDoFloty(const Identyfikator& floty, const Identyfikator& id, const Ilosc& ilosc){
	auto i = listaStatkow.find(id);
	if(i!=listaStatkow.end()){
		auto f = listaFlot.find(floty);
		if(f!=listaFlot.end()){
			if(ilosc <= i->second->pobierzIlosc()){
				if(ilosc < i->second->pobierzIlosc()){
					auto p = shared_ptr<Statek>(i->second->podziel(ilosc));
					if(f->second->dodajStatek(p)){
						return true;
					}else{
						i->second->polacz(*p);
						return false;
					}
				}else{
					if(f->second->dodajStatek(i->second)){
						listaStatkow.erase(i);
						listaObiektowZaladunkowych.erase(id);
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

bool Planeta::zaladujFlote(const Identyfikator& floty, const Identyfikator& id, const Ilosc& ilosc){
	auto i = listaObiektowZaladunkowych.find(id);
	if(i==listaObiektowZaladunkowych.end())
		return false;

	if(ilosc <= Ilosc(0.0) || i->second->pobierzIlosc() < ilosc)
		return false;

	auto f = listaFlot.find(floty);
	if(f==listaFlot.end())
		return false;
	shared_ptr<Obiekt> ptr = shared_ptr<Obiekt>( i->second->podziel(ilosc));
	if(!f->second->dodajLadunek(ptr)){
		i->second->polacz(*ptr);
		return false;
	}
	return true;
}

bool Planeta::czyMaWlasciciela()const{
	return wlasciciel!=nullptr;
}

void Planeta::rozladujStatek( shared_ptr< Statek > statek ){
	if(statek){
		for(auto element : statek->oproznijLadownie()){
			wybuduj(element.second);
		}
	}
}

shared_ptr< Flota > Planeta::pobierzFlote(const Identyfikator& identyfikator) const{
	auto i = listaFlot.find(identyfikator);
	if(i!=listaFlot.end())
		return i->second;
	return nullptr;
}

bool Planeta::usunFlote(const Identyfikator& identyfikator){
	return listaFlot.erase(identyfikator) != 0;
}


bool Planeta::zapisz( TiXmlElement* e ) const{
	TiXmlElement* n = new TiXmlElement(WEZEL_XML_PLANETA);
	e->LinkEndChild( n );
	idFloty.zapisz(n);
	TiXmlElement* c = new TiXmlElement(WEZEL_XML_OBIEKTY);
	n->LinkEndChild( c );
	for(auto o :  listaObiektow)
		if(!o.second->zapisz(c))
			return false;
	TiXmlElement* f = new TiXmlElement(WEZEL_XML_FLOTY);
	n->LinkEndChild( f );
	for(auto o :  listaFlot)
		if(!o.second->zapisz(f))
			return false;
	return Bazowa::zapisz(n);
}

bool Planeta::odczytaj( TiXmlElement* e ){
	if(e){
		TiXmlElement* o = e->FirstChildElement(WEZEL_XML_OBIEKTY);
		if(o)
			for(TiXmlElement* n = o->FirstChildElement(); n != nullptr ; n = n->NextSiblingElement()){
				Identyfikator identyfikator;
				if(!XmlBO::WczytajAtrybut<NOTHROW>(n,ATRYBUT_XML_IDENTYFIKATOR,identyfikator))
					return false;
				wybuduj(identyfikator,Ilosc(0));
				auto i = listaObiektow.find(identyfikator);
				if( i == listaObiektow.end() || !i->second->odczytaj(n) )
					return false;
			}
		TiXmlElement* f = e->FirstChildElement(WEZEL_XML_FLOTY);
		if(f)
			for(TiXmlElement* n = o->FirstChildElement(); n != nullptr ; n = n->NextSiblingElement()){
				Identyfikator identyfikator;
				if(!XmlBO::WczytajAtrybut<NOTHROW>(n,ATRYBUT_XML_IDENTYFIKATOR,identyfikator))
					return false;
				shared_ptr<Flota> ptr = shared_ptr<Flota>(new Flota (identyfikator,Identyfikator(),Identyfikator(),Flota::CelPodrozy::Transport));
				auto i = listaFlot.find(identyfikator);
				if( i != listaFlot.end() )
					return false;
				listaFlot.insert(make_pair(ptr->pobierzIdentyfikator(),ptr));
			}
		return Bazowa::odczytaj(e);
	}
	return false;
}

string Planeta::napis() const{
	Logger str(NAZWAKLASY(Planeta));
	str.dodajKlase(Bazowa::napis());
	for( auto i : listaObiektow )
		str.dodajPole("Obiekt", *(i.second));
	return str.napis();
}
