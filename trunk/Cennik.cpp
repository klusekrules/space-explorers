#include "Cennik.h"
#include "Logger.h"
#include "Surowce.h"
#include "Aplikacja.h"
#include "XmlBO.h"
#include "definicjeWezlowXML.h"

Cennik::Cennik( TiXmlElement* n ) throw(WyjatekParseraXML)
	: zmCzasuBudowy(nullptr)
{
	if(n){
		auto c = XmlBO::ZnajdzWezelJezeli<NOTHROW>(n->FirstChildElement(WEZEL_XML_CZAS),WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,WEZEL_XML_CZAS);
		if(c)
			zmCzasuBudowy=Aplikacja::getInstance().getGra().getZmianaFabryka().Tworz(c);
		auto e = n->FirstChildElement(WEZEL_XML_CENA);
		while(e){
			elementy.push_back(shared_ptr<Cena>(new Cena(e)));
			e = e->NextSiblingElement(WEZEL_XML_CENA);
		}
	}
}
Cennik::Cennik( const Cennik& o )
	: zmCzasuBudowy(nullptr)
{
	this->operator=(o);
}

Cennik& Cennik::operator=( const Cennik& o ){
	Zbiornik tmp;
	for(auto e : o.elementy){
		if(e)
			tmp.push_back(shared_ptr<Cena>(e->Kopia()));
	}
	elementy = tmp;
	return *this;
}

bool Cennik::czySpelniaKoszty( const Ilosc& i, const PodstawoweParametry& p ) const{
	for( auto e : elementy )
		if(e)
			if(!e->czySpelniaKoszty(i,p))
				return false;
	return true;
}

Czas Cennik::pobierzCzasBudowy( const PodstawoweParametry& p )const{
	auto k = PobierzKoszty(Ilosc(1),p);
	Czas suma;
	for( auto i : k ){
		if(i)
			suma+=i->pobierzCzas();
	}
	if(zmCzasuBudowy){		
		suma = zmCzasuBudowy->policzWartosc(suma(),static_cast<int>(p.getPoziom()()),p.getIdPlanety()());
	}
	return suma;
}

Cennik::ListaSurowcow Cennik::PobierzKoszty(const Ilosc& il, const PodstawoweParametry& p) const{
	ListaSurowcow tmp;
	for( auto i : elementy ){
		if(i)
			tmp.push_back(i->PobierzKoszty(il,p));
	}
	return tmp;
}

string Cennik::toString()const{
	Logger str(CLASSNAME(Cennik));
	for(auto i : elementy)
		if(i)
			str.addField("Element",*i);
	return str.toString();
}