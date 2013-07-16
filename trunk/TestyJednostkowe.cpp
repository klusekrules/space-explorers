#include "TestyJednostkowe.h"
#include <iostream>
#include "OgolnyWyjatek.h"

TestyJednostkowe::TestyJednostkowe()
{
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
		Log::pobierzInstancje().info("Inicjalizacja testów...");
		Log::pobierzInstancje().info("---------------------------------");
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
		Log::pobierzInstancje().info("Zakoñczono inicjalizacjê testów");
		Log::pobierzInstancje().info("---------------------------------");
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
				Log::pobierzInstancje().error(e.generujKomunikat());
			}catch(exception& e){
				Log::pobierzInstancje().error(e.what());
			}
		}
	}catch(OgolnyWyjatek& e){
		Log::pobierzInstancje().error(e.generujKomunikat());
	}catch(exception& e){
		Log::pobierzInstancje().error(e.what());
	}catch(...){
		Log::pobierzInstancje().error("Wyst¹pi³ nieznany wyjatek!");
	}
	Log::pobierzInstancje().info("Czyszczenie testów...");
	Log::pobierzInstancje().info("---------------------------------");
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
			Log::pobierzInstancje().error(e.generujKomunikat());
		}catch(exception& e){
			Log::pobierzInstancje().error(e.what());
		}catch(...){
			Log::pobierzInstancje().error("Wyst¹pi³ nieznany wyjatek!");
		}
	}
	Log::pobierzInstancje().info("Zakoñczono czyszczenie testów");
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
	str << "Przeprowadzono: " << poprawneTesty + bledy + bledyKrytyczne << ", bledy: "<< bledy + bledyKrytyczne << ", krytyczne: "<< bledyKrytyczne << ", pominieto: "<<pominieteTesty;
	Log::pobierzInstancje().info("---------------------------------");
	Log::pobierzInstancje().info("");
	Log::pobierzInstancje().info("Podsumowanie testów:");
	Log::pobierzInstancje().info(str.str());
}