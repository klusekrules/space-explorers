#include "Warunek.h"
#include "Logger.h"
#include "Aplikacja.h"
#include "ObiektBaseInfo.h"
#include "XmlBO.h"
#include "ZmianaFabryka.h"

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
				if(e->Value() == string("Wymog") ){
					ticpp::Element* firstElement = XmlBO::IterateChildrenElement(e,ObiektBaseInfo::LogObiektBaseInfo::className(),false);
					if(firstElement){
						auto first = shared_ptr<ObiektBaseInfo>(new ObiektBaseInfo(firstElement));
						auto second = ZmianaFabryka::pobierzInstancje().Tworz(XmlBO::IterateChildrenElement(e,"Zmiana",false));
						dodajWarunek(make_pair(first,second));
					}
				}
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
		if((*iter).first->getId() == o.first->getId()){
			if( (*iter).first->getPoziom() < o.first->getPoziom() ){
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
	for(auto a : warunki){
		str.startSubClass("Wymog");		
		str.addField<ObiektBaseInfo>("Wymog",*(a.first));
		str.addField<ZmianaInterfejs>("Wymog",*(a.second));
		str.endSubClass();
	}
	return str.toString();
}