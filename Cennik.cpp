#include "Cennik.h"
#include "Logger.h"
#include "Cena.h"
#include "CenaLiniowyDekorator.h"

Cennik::Cennik( ticpp::Node* n )
{
	if(n){
		auto e = n->FirstChildElement(false);
		while(e){
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
	//TODO: logowanie wektora
	//str.addField("Elementy",elementy);
	return str.toString();
}