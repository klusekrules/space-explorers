#include "Warunek.h"


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

bool Warunek::sprawdzWarunki( ListaWarunkow& a ){
	for( auto w : warunki ){
		if( !spelnienieWarunku (*w, a ) ){
			return false;
		}
	}
	return true;
}