#include "TestyJednostkowe.h"
#include <iostream>
#include <sstream>
#include "TypyProste\Wyjatek.h"
#include "Logger\Log.h"
#include "Kontroler\Aplikacja.h"
#include "Kontroler\Gra.h"

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
	aplikacja.instancjaGry_ = std::make_shared<SpEx::Gra>(aplikacja.logger_, aplikacja.pobierzZarzadceLokacji(), aplikacja.ustawienia_);
	try{
#ifndef LOG_OFF_ALL
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Inicjalizacja testów...");
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "---------------------------------");
#endif
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
				throw STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(), STyp::Tekst(), STyp::Identyfikator(), STyp::Tekst("B³ad Ogólny"), STyp::Tekst("Nie udana inicjalizacja testów!"));
		}
#ifndef LOG_OFF_ALL
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Zakoñczono inicjalizacjê testów");
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "---------------------------------");
#endif
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
#ifndef LOG_OFF_ALL
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, e.generujKomunikat());
#endif
			}catch(std::exception& e){
#ifndef LOG_OFF_ALL
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, e.what());
#endif
			}
		}
	}catch(STyp::Wyjatek& e){
#ifndef LOG_OFF_ALL
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, e.generujKomunikat());
#endif
	}catch(std::exception& e){
#ifndef LOG_OFF_ALL
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, e.what());
#endif
	}catch (WyjatekSprawdzeniaWarunku& e){
#ifndef LOG_OFF_ALL
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, e.komunikat());
#endif
	}catch(...){
#ifndef LOG_OFF_ALL
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Wyst¹pi³ nieznany wyjatek!");
#endif
	}
#ifndef LOG_OFF_ALL
	SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Czyszczenie testów...");
	SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "---------------------------------");
#endif
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
#ifndef LOG_OFF_ALL
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, e.generujKomunikat());
#endif
		}catch(std::exception& e){
#ifndef LOG_OFF_ALL
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, e.what());
#endif
		}catch (WyjatekSprawdzeniaWarunku& e){
#ifndef LOG_OFF_ALL
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, e.komunikat());
#endif
		}catch (...){
#ifndef LOG_OFF_ALL
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Wyst¹pi³ nieznany wyjatek!");
#endif
		}
	}
#ifndef LOG_OFF_ALL
	SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Zakoñczono czyszczenie testów");
#endif
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
#ifndef LOG_OFF_ALL
	std::stringstream str;
	str << "Przeprowadzono: " << poprawneTesty + bledy << ", bledy: "<< bledy << ", krytyczne: "<< bledyKrytyczne << ", pominieto: "<<pominieteTesty;
	SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "---------------------------------");
	SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "");
	SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Podsumowanie testów:");
	SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, str.str());
#endif
}