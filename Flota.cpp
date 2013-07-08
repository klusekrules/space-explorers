#include "Flota.h"
#include "Aplikacja.h"

Flota::Flota(const IdType& id)
	: Base(id)
{
}

Flota::~Flota(void)
{
}

bool Flota::dodajStatek( shared_ptr<Statek> ptr ){
	if(!ptr)
		return false;
	auto iter = lista.find(ptr->ID());
	if(iter == lista.end()){
		ptr->setIdPlanety(IdType());
		lista.insert(make_pair(ptr->ID(),ptr));
	}else{
		return iter->second->Polacz( *ptr );
	}
	return true;
}

bool Flota::dodajLadunek( shared_ptr<Obiekt> ptr ){
	if(!ptr)
		return false;
	Objetosc obj = pobierzDostepneMiejsce();
	if(obj < ptr->getObjetosc())
		return false;
	for( auto i : lista ){
		if(i.second->DodajObiektDoLadowni(*ptr))
			return true;
	}
	return false;
}

Objetosc Flota::pobierzDostepneMiejsce() const{
	Objetosc suma(0.0);
	for(auto a : lista){
		suma+=a.second->getPojemnoscMax() - a.second->getZajeteMiejsce();
	}
	return suma;
}

bool Flota::zapisz( TiXmlElement* e ) const{
	if(e){
		TiXmlElement* n = new TiXmlElement(CLASSNAME(Flota));
		e->LinkEndChild( n );
		for(auto s : lista)
			if(s.second)
				s.second->zapisz(n);
		return Base::zapisz(n);
	}
	return false;
}

bool Flota::odczytaj( TiXmlElement* e ) {
	if(e && Base::odczytaj(e)){
		for(TiXmlElement* n = e->FirstChildElement(); n != nullptr ; n = n->NextSiblingElement()){
			auto c = n->Attribute("id");
			if(!c)
				return false;
			IdType id(stoi(c,nullptr,0));
			shared_ptr<Statek> p = shared_ptr<Statek>(Aplikacja::getInstance().getGra().getStatek(id).TworzEgzemplarz(Ilosc(),IdType()));			
			if(!p->odczytaj(n) )
				return false;
			lista.insert(make_pair(p->ID(),p));
		}
	}
	return false;
}

string Flota::toString()const {
	Logger str(CLASSNAME(Ladownia));
	str.addClass(Base::toString());
	for(auto s : lista)
		if(s.second)
			str.addField(CLASSNAME(Statek),*s.second);
	return str.toString();
}
