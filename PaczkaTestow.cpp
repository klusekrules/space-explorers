#include "PaczkaTestow.h"
#include "WyjatekSprawdzeniaWarunku.h"
#include <iostream>
#include "Logger\Log.h"
#include <sstream>

void PaczkaTestow::startTestow(){
}

void PaczkaTestow::koniecTestow(){
}

void PaczkaTestow::dodajTest(const std::string& nazwa, std::function<void()> test){
	zbiorTestow_.push_back(std::make_pair(nazwa, test));
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
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, e.komunikat());
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

void PaczkaTestow::ustawNazwe(const std::string& napis){
	nazwa_ = napis;
}

void PaczkaTestow::naglowek(){
	std::stringstream str;
	str<< "Klasa: "<< nazwa_ << "... Testy: "<< zbiorTestow_.size();
	SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, str.str());
}
 
void PaczkaTestow::podsumowanie(){
	std::stringstream str;
	str << "Przeprowadzono: " << poprawneTesty + bledy << ", bledy: "<< bledy << ", krytyczne: "<< bledyKrytyczne << ", pominieto: "<<pominieteTesty;
	SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, str.str());
	SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "---------------------------------");
}
