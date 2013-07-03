#include "Cennik.h"
#include "Logger.h"

Cennik::Cennik( ticpp::Node* n ) throw(WyjatekParseraXML)
{
	if(n){
		auto e = n->FirstChildElement(false);
		while(e){
			if(e->Value() == CLASSNAME(Cena))
				elementy.push_back(shared_ptr<Cena>(new Cena(e)));
			e = e->NextSiblingElement(false);
		}
	}
}
Cennik::Cennik( const Cennik& o )
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