#include "Warunek.h"
#include "Logger.h"
#include "Aplikacja.h"
#include "ObiektBaseInfo.h"
#include "XmlBO.h"
#include "FuncTransf\ZmianaFabryka.h"

Warunek::Warunek(const Warunek& w)
{
	this->operator=(w);
}

Warunek::Warunek( ticpp::Node* n ) throw(WyjatekParseraXML)
{
	if(n){
		try{
			auto e = n->FirstChildElement(false);
			while(e){
				if(e->Value() == string("Wymog") ){
					ticpp::Element* firstElement = XmlBO::IterateChildrenElement<NOTHROW>(e,CLASSNAME(ObiektBaseInfo));
					if(firstElement){
						auto first = shared_ptr<ObiektBaseInfo>(new ObiektBaseInfo(firstElement));
						auto second = Aplikacja::getInstance().getGra().getZmianaFabryka().Tworz(XmlBO::IterateChildrenElement<NOTHROW>(e,"Zmiana"));
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

Warunek& Warunek::operator=(const Warunek& w){
	warunki.clear();
	for(auto e : w.warunki){
		Item i(nullptr,nullptr);
		if(e.first)
			i.first = shared_ptr<ObiektBaseInfo>(new ObiektBaseInfo(*e.first));
		if(e.second)
			i.second = shared_ptr<ZmianaInterfejs>(e.second->Kopia());
		warunki.push_back(i);
	}
	return *this;
}

bool Warunek::dodajWarunek( Item& o ){
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

bool Warunek::czySpelniaWarunki( const PodstawoweParametry& p ) const{	
	if(warunki.empty())
		return true;
	const Planeta& planeta = Aplikacja::getInstance().getGra().getUzytkownik().getPlaneta(p.getIdPlanety());
	for (auto a : warunki){
		Poziom poz;
		if(a.second)
			poz = Poziom(static_cast<Poziom::type_name>(a.second->value(a.first->getPoziom(),p.getPoziom(),p.getIdPlanety())));
		else
			poz = a.first->getPoziom();

		if(planeta.pobierzObiekt(a.first->getId()).getPoziom()<poz)
			return false;
	}
	return true;
}

Warunek::PrzetworzoneWarunki Warunek::listaWarunkow( const PodstawoweParametry& p ) const{
	PrzetworzoneWarunki tmp;
	for (auto a : warunki)
		tmp.push_back(przeliczWarunek(a,p));
	return tmp;
}


shared_ptr< ObiektBaseInfo > Warunek::przeliczWarunek( Item& o , const PodstawoweParametry& p ) const{
	if(o.second)
		return shared_ptr< ObiektBaseInfo > ( new ObiektBaseInfo( *(o.first), Poziom( static_cast<Poziom::type_name>(floorl(o.second->value( o.first->getPoziom().value() , static_cast<int>(p.getPoziom().value()),p.getIdPlanety().value() ))) ) ) );
	else
		return shared_ptr< ObiektBaseInfo > ( new ObiektBaseInfo( *(o.first), Poziom( o.first->getPoziom() ) ) );
}

string Warunek::toString() const{
	Logger str(CLASSNAME(Warunek));
	for(auto a : warunki){
		str.startSubClass("Wymog");		
		str.addField("Wymog",*(a.first));
		str.addField("Wymog",*(a.second));
		str.endSubClass();
	}
	return str.toString();
}