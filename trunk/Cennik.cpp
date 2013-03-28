#include "Cennik.h"
#include "Logger.h"

Cennik::Cennik( ticpp::Node* n )
{
	if(n){
		auto e = n->FirstChildElement(false);
		while(e){
			//Wyniesc to do nowej klasy, ( fabryka obiektów)
			if(e->Value() == Cena::LogCena::className())
				elementy.push_back(shared_ptr<Cena>(new Cena(e)));
			e = e->NextSiblingElement(false);
		}
	}
}

Cennik::~Cennik(){
}

Cennik& Cennik::operator=( const Cennik& c){
	Zbiornik tmp;
	for(auto e : c.elementy){
		tmp.push_back(shared_ptr<Cena>(e->Kopia()));
	}
	elementy = tmp;
	return *this;
}

bool Cennik::czySpelniaWymagania( const Ilosc& i, const Poziom& p, const IdType& id ) const{
	for( auto e : elementy )
		if(!e->czySpelniaWymagania(i,p,id))
			return false;
	return true;
}

Cennik::ListaSurowcow Cennik::PobierzKoszty(const Ilosc& il, const Poziom& p) const{
	ListaSurowcow tmp;
	for( auto i : elementy ){
		tmp.push_back(i->PobierzKoszty(il,p));
	}
	return tmp;
}

string Cennik::toString()const{
	Logger str(LogCennik::className());
	for(auto i : elementy)
		if(i)
			str.addField("Element",*i);
	return str.toString();
}