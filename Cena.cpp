
#include "Biblioteki.h"
/*
Cena::Cena()
	: koszty()
{
}

Cena::Cena( const SPG::ZbiornikObiektow& zsKoszty )
	: koszty(zsKoszty)
{
}

Cena::Cena( const Cena& a ){
	for( auto iter = a.koszty.begin(); iter != a.koszty.end(); iter++){
		koszty.insert(make_pair( iter->first , iter->second->Kopia() ));
	}
}

Cena::~Cena(){
	for( auto iter = koszty.begin(); iter != koszty.end(); iter++){
		delete iter->second;
	}
}

SPG::ZbiornikObiektow Cena::PobierzKoszty() const{
	SPG::ZbiornikObiektow zbiornik;
	for( auto iter = koszty.begin(); iter != koszty.end(); iter++){
		zbiornik.insert(make_pair( iter->first , iter->second->Kopia() ));
	}
	return zbiornik;
}

SPG::ZbiornikObiektow Cena::getKoszty() const{
	SPG::ZbiornikObiektow zbiornik;
	for( auto iter = koszty.begin(); iter != koszty.end(); iter++){
		zbiornik.insert(make_pair( iter->first , iter->second->Kopia() ));
	}
	return zbiornik;
}

void Cena::setKoszty( const SPG::ZbiornikObiektow& zsKoszty ){
	for( auto iter = koszty.begin(); iter != koszty.end(); iter++){
		delete iter->second;
	}
	koszty = zsKoszty;
}

string Cena::toString() const{
	Logger str("Cena");
	str.dodajMapaParKC("Zawartosc",koszty);
	return str.toString();
}*/