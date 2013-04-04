#include "Warunek.h"
#include "Logger.h"
#include "Aplikacja.h"
#include "ObiektBaseInfo.h"

Warunek::Warunek(){
}

Warunek::Warunek(const Warunek& w)
	: warunki(w.warunki)
{
}

Warunek::Warunek( ticpp::Node* n ){
	if(n){
		try{
			auto e = n->FirstChildElement(false);
			while(e){
				if(e->Value() == ObiektBaseInfo::LogObiektBaseInfo::className())
					dodajWarunek(shared_ptr<ObiektBaseInfo>(new ObiektBaseInfo(e)));
				e = e->NextSiblingElement(false);
			}
		}catch(exception& e){
			throw WyjatekParseraXML(EXCEPTION_PLACE,e,WyjatekParseraXML::trescBladStrukturyXml);
		}
	}
}

const Warunek& Warunek::operator=(const Warunek& w){
	warunki=w.warunki;
	return *this;
}

bool Warunek::dodajWarunek( Item o ){
	for(auto iter = warunki.begin() ; iter != warunki.end() ; ++iter ){
		if((*iter)->getId() == o->getId()){
			if( (*iter)->getPoziom() < o->getPoziom() ){
				warunki.erase(iter);
				warunki.push_back(o);
				return true;
			}else{
				return false;
			}
		}
	}
	warunki.push_back(o);
	return true;
}

Warunek::~Warunek()
{
}

bool Warunek::czySpelniaWarunki( const IdType& idPlanety ) const{	
	if(warunki.empty())
		return true;
	/*const ObiektBase& ob = Aplikacja::getInstance().getObiekt(idPlanety);
	for( auto w : warunki ){
		w->getPoziom() <= ob.getPoziom();
	}*/
	return true;
}

string Warunek::toString() const{
	Logger str(className());
	for(auto a : warunki)
		str.addField("ID Warunku",a->getId());
	return str.toString();
}