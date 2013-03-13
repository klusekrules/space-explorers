#include "Warunek.h"
#include "Logger.h"
#include "Aplikacja.h"
Warunek::Warunek()
{
}

Warunek::Warunek(const Warunek& w){
	for( auto o : w.warunki ){
		warunki.push_back(o->Kopia());
	}
}

const Warunek& Warunek::operator=(const Warunek& w){
	for( auto o : warunki ){
		delete o;
	}
	warunki.clear();
	for( auto o : w.warunki ){
		warunki.push_back(o->Kopia());
	}
	return *this;
}

bool Warunek::dodajWarunek( const ObiektBase& o ){
	for(size_t a = 0 ; a < warunki.size() ; ++a ){
		if(warunki[a]->getId() == o.getId()){
			if( warunki[a]->getPoziom() < o.getPoziom() ){
				delete warunki[a];
				warunki[a] = o.Kopia();
				return true;
			}else{
				return false;
			}
		}
	}
	warunki.push_back(o.Kopia());
	return true;
}

bool Warunek::usunWarunek( const ObiektBase& o ){
	for(auto iter = warunki.begin() ; iter != warunki.end() ; ++iter ){
		if((*iter)->getId() == o.getId()){
			if( (*iter)->getPoziom() == o.getPoziom() ){
				delete (*iter);
				warunki.erase(iter);
				return true;
			}else{
				return false;
			}
		}
	}
	return false;
}


Warunek::~Warunek()
{
	for( auto w : warunki ){
		delete w;
	}
}

bool Warunek::sprawdzWarunki( const IdType& idPlanety ){
	const ObiektBase& ob = Aplikacja::getInstance().getObiekt(idPlanety); // TODO: Pobieranie planety zamiast obiektu, nastêpnie pobieranie obiektu z planety.
	for( auto w : warunki ){
		w->getPoziom() <= ob.getPoziom();
	}
	return true;
}

string Warunek::toString() const{
	Logger str(className());
	for(auto a : warunki)
		str.addField("ID Warunku",a->getId());
	return str.toString();
}