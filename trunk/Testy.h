#pragma once
#include "Main.h"
#include "Biblioteki.h"
#include "ObiektList.hpp"
#include "StatekInfo.h"
#include "SurowceInfo.h"
#include "Aplikacja.h"
#include <chrono>

class Testy
{
private:
	Statek* tworzStatek(const Klucz& id,const Ilosc& i)const throw (OgolnyWyjatek,NieznalezionoObiektu);
	Surowce* tworzSurowce(const Klucz& id,const Ilosc& i)const throw (OgolnyWyjatek,NieznalezionoObiektu);
	
	bool ladowanie_danych() const;

	/* */
	static unsigned int bledy;
	static unsigned int testy;
	static unsigned int fatalError;
	static unsigned int bledyGlobal;
	static unsigned int testyGlobal;
	static unsigned int fatalErrorGlobal;
	static chrono::steady_clock::time_point startlocal;
	static chrono::steady_clock::time_point endlocal;
	static chrono::steady_clock::time_point start;
	static chrono::steady_clock::time_point end;
	static string modulName;
	
	static void startTest();
	static void endTest();
	
	static void startTestModul(string name);
	static bool assert_false( const Tekst& tPlik, const Ilosc& iLinia, bool a );
	static bool assert_true( const Tekst& tPlik, const Ilosc& iLinia, bool a );
	static bool endTestModul();
	static bool endTestModulImidaite();
	/* */

public:

	//Inicjalizacja * init;

	Testy();
	~Testy();
	void run() const;

	bool test_tworzenieObiektow()const;
	bool test_KlasaObiektList()const;
	bool test_KlasaLadownia()const;
	bool test_KlasaJednostkaAtakujaca()const;
	bool test_KlasaNiepoprawneParametryFunkcji() const;
	bool test_wymagan()const;

	//void test_ladowaniePlikuXML();
	//void test_podzialuStatku();
	//void test_metodyToString();
};

