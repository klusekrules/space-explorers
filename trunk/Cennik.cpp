#include "Cennik.h"
#include "Logger.h"
#include "Surowce.h"
#include "Aplikacja.h"
#include "XmlBO.h"

Cennik::Cennik( TiXmlElement* n ) throw(WyjatekParseraXML)
	: zmCzasuBudowy(nullptr)
{
	if(n){
		auto c = XmlBO::ZnajdzWezelJezeli<NOTHROW>(n,"Zmiana","for","Czas");
		if(c)
			zmCzasuBudowy=Aplikacja::getInstance().getGra().getZmianaFabryka().Tworz(c);
		auto e = n->FirstChildElement();
		while(e){
			if(e->Value() == CLASSNAME(Cena))
				elementy.push_back(shared_ptr<Cena>(new Cena(e)));
			e = e->NextSiblingElement();
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
		suma = zmCzasuBudowy->value(suma(),static_cast<int>(p.getPoziom()()),p.getIdPlanety()());
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