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
		Log::pobierzInstancje().info("Inicjalizacja test�w...");
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
				throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(),Tekst("B�ad Og�lny"),Tekst("Nie udana inicjalizacja test�w!"));
		}
		Log::pobierzInstancje().info("Zako�czono inicjalizacj� test�w");
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
		Log::pobierzInstancje().error("Wyst�pi� nieznany wyjatek!");
	}
	Log::pobierzInstancje().info("Czyszczenie test�w...");
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
			Log::pobierzInstancje().error("Wyst�pi� nieznany wyjatek!");
		}
	}
	Log::pobierzInstancje().info("Zako�czono czyszczenie test�w");
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
	Log::pobierzInstancje().info("Podsumowanie test�w:");
	Log::pobierzInstancje().info(str.str());
}