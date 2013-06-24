#include "Test.h"
#include "Aplikacja.h"
#include "Testy.h"

Test::Test( Testy& t, const string& modul, FunkcjaTestowa funkcjaTestowa , bool czyKrytyczny  )
	: testy(t), modul(modul), funkcja(funkcjaTestowa), krytyczny(czyKrytyczny)
{
}

Test::~Test()
{
}

void Test::wykonanoTest(){
	++uTesty;
	testy.wykonanoTest();
}

void Test::wykrytoBlad(){
	++uBledy;
	testy.wykrytoBlad();
}

void Test::wykrytoBladKrytyczny(){
	++uFatalError;
	testy.wykrytoBladKrytyczny();
}

bool Test::assert_false( const Tekst& tPlik, const Ilosc& iLinia, bool a ){
	wykonanoTest();
	if(!a){
		Aplikacja::getInstance().getLog().error("Wykryto niepoprawny rezultat testu");
		Aplikacja::getInstance().getLog().error("Plik:");
		Aplikacja::getInstance().getLog().error( tPlik );
		Aplikacja::getInstance().getLog().error("Linia:");
		Aplikacja::getInstance().getLog().error( iLinia );
		wykrytoBlad();
		return false;
	}
	return true;
}
bool Test::assert_true( const Tekst& tPlik, const Ilosc& iLinia, bool a ){
	wykonanoTest();
	if(a){
		Aplikacja::getInstance().getLog().error("Wykryto niepoprawny rezultat testu");
		Aplikacja::getInstance().getLog().error("Plik:");
		Aplikacja::getInstance().getLog().error( tPlik );
		Aplikacja::getInstance().getLog().error("Linia:");
		Aplikacja::getInstance().getLog().error( iLinia );
		wykrytoBlad();
		return false;
	}
	return true;
}

void Test::startTestModul(){
	uBledy=0;
	uTesty=0;
	uFatalError=0;
	Aplikacja::getInstance().getLog().info("----------------------------------------------");
	Aplikacja::getInstance().getLog().info("           Rozpoczêcie testów modu³u           ");
	Aplikacja::getInstance().getLog().info(modul);
	Aplikacja::getInstance().getLog().info("----------------------------------------------");
	startlocal = chrono::steady_clock::now();
}


void Test::endTestModul(){	
	stringstream s,st;
	endlocal = chrono::steady_clock::now();
	st<<"Czas trwania testu: "<<chrono::duration_cast<chrono::milliseconds>(endlocal - startlocal).count()<< "ms.";
	s<<"Liczba Testów: "<<uTesty<<" , Liczba B³êdów: "<<uBledy;
	Aplikacja::getInstance().getLog().info("----------------------------------------------");
	Aplikacja::getInstance().getLog().info("           Zakoñczenie testów modu³u           ");
	Aplikacja::getInstance().getLog().info(modul);
	Aplikacja::getInstance().getLog().info(s.str());
	Aplikacja::getInstance().getLog().info(st.str());
	Aplikacja::getInstance().getLog().info("----------------------------------------------");
}

bool Test::endTestModulImidaite(){
	stringstream s,st;
	endlocal = chrono::steady_clock::now();
	st<<"Czas trwania testu: "<<chrono::duration_cast<chrono::milliseconds>(endlocal - startlocal).count()<< "ms.";
	s<<"Wykryto b³¹d krytyczny.\nPrzerwno dalsze dzia³anie metody testujacej.";
	Aplikacja::getInstance().getLog().info("----------------------------------------------");
	Aplikacja::getInstance().getLog().info("           Zakoñczenie testów modu³u           ");
	Aplikacja::getInstance().getLog().info(modul);
	Aplikacja::getInstance().getLog().info(s.str());
	Aplikacja::getInstance().getLog().info(st.str());
	Aplikacja::getInstance().getLog().info("----------------------------------------------");
	wykrytoBladKrytyczny();
	return !krytyczny;
}


bool Test::operator()(){
	startTestModul();
	try{
		funkcja(*this);
	}catch(exception& e){
		Aplikacja::getInstance().getLog().error(e.what());
		return endTestModulImidaite();
	}catch(OgolnyWyjatek& e){
		Aplikacja::getInstance().getLog().error(e.generujKomunikat());
		return endTestModulImidaite();
	}
	endTestModul();
	return true;
}

