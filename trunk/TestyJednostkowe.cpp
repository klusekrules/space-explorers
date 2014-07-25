#include "TestyJednostkowe.h"
#include <iostream>
#include <sstream>
#include "TypyProste\Wyjatek.h"
#include "Logger\Log.h"
#include "Aplikacja.h"

void TestyJednostkowe::inicjalizacjaDanych( PaczkaTestow* paczka ){
	inicjalizacja_.push_back(paczka);
}

void TestyJednostkowe::czyszczenieDanych( PaczkaTestow* paczka ){
	czyszczenie_.push_back(paczka);
}

void TestyJednostkowe::dodajPaczke( PaczkaTestow* paczka ){
	zbiorTestow_.push_back(paczka);
}

TestyJednostkowe& TestyJednostkowe::pobierzInstancje(){
	static TestyJednostkowe obiekt;
	return obiekt;
}

void TestyJednostkowe::wykonajTesty(){

	auto kopia = SpEx::Aplikacja::pobierzInstancje().instancjaGry_;
	auto& aplikacja = SpEx::Aplikacja::pobierzInstancje();
	aplikacja.instancjaGry_ = std::make_shared<SpEx::Gra>(aplikacja.logger_, aplikacja.pobierzZarzadceLokacji(), aplikacja.pobierzZarzadcePamieci());
	try{
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Inicjalizacja test�w...");
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "---------------------------------");
		for( auto a : inicjalizacja_ ){
			try{
				a->wykonajTesty();
				bledy+=a->bledy;
				bledyKrytyczne+=a->bledyKrytyczne;
				pominieteTesty+=a->pominieteTesty;
				poprawneTesty+=a->poprawneTesty;
			}catch(...){
				bledy+=a->bledy;
				bledyKrytyczne+=a->bledyKrytyczne;
				pominieteTesty+=a->pominieteTesty;
				poprawneTesty+=a->poprawneTesty;
				throw;
			}
			if(a->bledy>0)
				throw STyp::Wyjatek(EXCEPTION_PLACE,STyp::Tekst(),STyp::Identyfikator(),STyp::Tekst("B�ad Og�lny"),STyp::Tekst("Nie udana inicjalizacja test�w!"));
		}
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Zako�czono inicjalizacj� test�w");
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "---------------------------------");
		for( auto a : zbiorTestow_ ){
			try{
				try{
					a->wykonajTesty();
					bledy+=a->bledy;
					bledyKrytyczne+=a->bledyKrytyczne;
					pominieteTesty+=a->pominieteTesty;
					poprawneTesty+=a->poprawneTesty;
				}catch(...){
					bledy+=a->bledy;
					bledyKrytyczne+=a->bledyKrytyczne;
					pominieteTesty+=a->pominieteTesty;
					poprawneTesty+=a->poprawneTesty;
					throw;
				}
			}catch(STyp::Wyjatek& e){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, e.generujKomunikat());
			}catch(std::exception& e){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, e.what());
			}
		}
	}catch(STyp::Wyjatek& e){
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, e.generujKomunikat());
	}catch(std::exception& e){
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, e.what());
	}catch (WyjatekSprawdzeniaWarunku& e){
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, e.komunikat());
	}catch(...){
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Wyst�pi� nieznany wyjatek!");
	}
	SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Czyszczenie test�w...");
	SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "---------------------------------");
	for( auto a : czyszczenie_ ){
		try{
			try{
				a->wykonajTesty();
				bledy+=a->bledy;
				bledyKrytyczne+=a->bledyKrytyczne;
				pominieteTesty+=a->pominieteTesty;
				poprawneTesty+=a->poprawneTesty;
			}catch(...){
				bledy+=a->bledy;
				bledyKrytyczne+=a->bledyKrytyczne;
				pominieteTesty+=a->pominieteTesty;
				poprawneTesty+=a->poprawneTesty;
				throw;
			}
		}catch(STyp::Wyjatek& e){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, e.generujKomunikat());
		}catch(std::exception& e){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, e.what());
		}catch (WyjatekSprawdzeniaWarunku& e){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, e.komunikat());
		}catch (...){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Wyst�pi� nieznany wyjatek!");
		}
	}
	SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Zako�czono czyszczenie test�w");
	podsumowanie();
	SpEx::Aplikacja::pobierzInstancje().instancjaGry_ = kopia;
}

TestyJednostkowe::~TestyJednostkowe(){
	for( auto a : inicjalizacja_ ){
		delete a;
	}
	for( auto a : zbiorTestow_ ){
		delete a;
	}
	for( auto a : czyszczenie_ ){
		delete a;
	}
}
 
void TestyJednostkowe::podsumowanie(){
	std::stringstream str;
	str << "Przeprowadzono: " << poprawneTesty + bledy << ", bledy: "<< bledy << ", krytyczne: "<< bledyKrytyczne << ", pominieto: "<<pominieteTesty;
	SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "---------------------------------");
	SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "");
	SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Podsumowanie test�w:");
	SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, str.str());
}