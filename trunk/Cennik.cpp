#include "Cennik.h"
#include "Logger.h"
#include "Cena.h"
#include "CenaLiniowyDekorator.h"

Cennik::Cennik( ticpp::Node* n )
{
	if(n){
		auto e = n->FirstChildElement(false);
		while(e){
			//Wyniesc to do nowej klasy, ( fabryka obiektów)
			if(e->Value() == Cena::LogCena::className())
				elementy.push_back(new Cena(e));
			if(e->Value() == CenaLiniowyDekorator::LogCenaLiniowyDekorator::className())
				elementy.push_back(new CenaLiniowyDekorator(e));
			e = e->NextSiblingElement(false);
		}
	}
}
bool Cennik::czySpelniaWymagania( const Ilosc& i, const IdType& id ) const{
	for( auto e : elementy )
		if(!e->czySpelniaWymagania(i,id))
			return false;
	return true;
}

Cennik::~Cennik(){
	for( auto e : elementy)
		if(e)
			delete e;
}

string Cennik::toString()const{
	Logger str(LogCennik::className());
	for(auto i : elementy)
		if(i)
			str.addField("Element",*i);
	return str.toString();
}