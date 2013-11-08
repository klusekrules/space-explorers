#include "TestyJednostkowe.h"
#include <iostream>
#include <sstream>
#include "OgolnyWyjatek.h"
#include "Logger\Log.h"

TestyJednostkowe::TestyJednostkowe(){
	bledy = 0;
	bledyKrytyczne = 0;
	pominieteTesty = 0;
	poprawneTesty = 0;
}

TestyJednostkowe::TestyJednostkowe( const TestyJednostkowe& obiekt ){

}

void TestyJednostkowe::inicjalizacjaDanych( PaczkaTestow* paczka ){
	inicjalizacja_.push_back(paczka);
}

void TestyJednostkowe::czyszczenieDanych( PaczkaTestow* paczka ){
	czyszczenie_.push_back(paczka);
}

TestyJednostkowe& TestyJednostkowe::operator=( const TestyJednostkowe& obiekt ){

	return *this;
}

void TestyJednostkowe::dodajPaczke( PaczkaTestow* paczka ){
	zbiorTestow_.push_back(paczka);
}

TestyJednostkowe& TestyJednostkowe::pobierzInstancje(){
	static TestyJednostkowe obiekt;
	return obiekt;
}

void TestyJednostkowe::wykonajTesty(){
	try{
		Log::pobierzInstancje().loguj(Log::Info,"Inicjalizacja testów...");
		Log::pobierzInstancje().loguj(Log::Info,"---------------------------------");
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
				throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(),Tekst("B³ad Ogólny"),Tekst("Nie udana inicjalizacja testów!"));
		}
		Log::pobierzInstancje().loguj(Log::Info,"Zakoñczono inicjalizacjê testów");
		Log::pobierzInstancje().loguj(Log::Info,"---------------------------------");
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
			}catch(OgolnyWyjatek& e){
				Log::pobierzInstancje().loguj(Log::Error,e.generujKomunikat());
			}catch(exception& e){
				Log::pobierzInstancje().loguj(Log::Error,e.what());
			}
		}
	}catch(OgolnyWyjatek& e){
		Log::pobierzInstancje().loguj(Log::Error,e.generujKomunikat());
	}catch(exception& e){
		Log::pobierzInstancje().loguj(Log::Error,e.what());
	}catch(...){
		Log::pobierzInstancje().loguj(Log::Error,"Wyst¹pi³ nieznany wyjatek!");
	}
	Log::pobierzInstancje().loguj(Log::Info,"Czyszczenie testów...");
	Log::pobierzInstancje().loguj(Log::Info,"---------------------------------");
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
		}catch(OgolnyWyjatek& e){
			Log::pobierzInstancje().loguj(Log::Error,e.generujKomunikat());
		}catch(exception& e){
			Log::pobierzInstancje().loguj(Log::Error,e.what());
		}catch(...){
			Log::pobierzInstancje().loguj(Log::Error,"Wyst¹pi³ nieznany wyjatek!");
		}
	}
	Log::pobierzInstancje().loguj(Log::Info,"Zakoñczono czyszczenie testów");
	podsumowanie();
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
	stringstream str;
	str << "Przeprowadzono: " << poprawneTesty + bledy << ", bledy: "<< bledy << ", krytyczne: "<< bledyKrytyczne << ", pominieto: "<<pominieteTesty;
	Log::pobierzInstancje().loguj(Log::Info,"---------------------------------");
	Log::pobierzInstancje().loguj(Log::Info,"");
	Log::pobierzInstancje().loguj(Log::Info,"Podsumowanie testów:");
	Log::pobierzInstancje().loguj(Log::Info,str.str());
}