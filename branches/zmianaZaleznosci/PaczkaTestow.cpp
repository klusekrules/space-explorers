#include "PaczkaTestow.h"
#include "WyjatekSprawdzeniaWarunku.h"
#include <iostream>
#include "Logger\Log.h"
#include <sstream>

PaczkaTestow::PaczkaTestow(){
	bledy = 0;
	bledyKrytyczne = 0;
	pominieteTesty = 0;
	poprawneTesty = 0;
}

void PaczkaTestow::startTestow(){
}

void PaczkaTestow::koniecTestow(){
}

void PaczkaTestow::dodajTest( const string& nazwa, function<void ()> test ){
	zbiorTestow_.push_back(make_pair(nazwa,test));
}

void PaczkaTestow::wykonajTesty(){
	bledy = 0;
	bledyKrytyczne = 0;
	pominieteTesty = 0;
	poprawneTesty = 0;
	naglowek();
	startTestow();
	for( auto a : zbiorTestow_ ){
		try{
			a.second();
			++poprawneTesty;
		}catch(WyjatekSprawdzeniaWarunku& e){
			e.ustawNazweMetody( a.first );
			++bledy;
			Log::pobierzInstancje().loguj(Log::Info,e.komunikat());
		}catch(...){
			++bledy;
			++bledyKrytyczne;
			pominieteTesty = static_cast<unsigned int>(zbiorTestow_.size()) - poprawneTesty - bledy;
			podsumowanie();
			throw;
		}
	}
	koniecTestow();
	podsumowanie();
}

void PaczkaTestow::ustawNazwe( const string& napis ){
	nazwa_ = napis;
}

void PaczkaTestow::naglowek(){
	stringstream str;
	str<< "Klasa: "<< nazwa_ << "... Testy: "<< zbiorTestow_.size();
	Log::pobierzInstancje().loguj(Log::Info,str.str());
}
 
void PaczkaTestow::podsumowanie(){
	stringstream str;
	str << "Przeprowadzono: " << poprawneTesty + bledy << ", bledy: "<< bledy << ", krytyczne: "<< bledyKrytyczne << ", pominieto: "<<pominieteTesty;
	Log::pobierzInstancje().loguj(Log::Info,str.str());
	Log::pobierzInstancje().loguj(Log::Info,"---------------------------------");
}

PaczkaTestow::~PaczkaTestow(void){
}
