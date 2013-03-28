#pragma once
#include "Main.h"
#include "Biblioteki.h"
#include "ObiektList.hpp"
#include "StatekInfo.h"
#include "SurowceInfo.h"
#include "Aplikacja.h"

class Testy
{
private:
	Statek* tworzStatek(const Klucz& id,const Ilosc& i)const throw (OgolnyWyjatek,NieznalezionoObiektu);
	Surowce* tworzSurowce(const Klucz& id,const Ilosc& i)const throw (OgolnyWyjatek,NieznalezionoObiektu);
	
	bool ladowanie_danych();

	/* */
	static unsigned int bledy;
	static unsigned int testy;
	static unsigned int fatalError;
	static unsigned int bledyGlobal;
	static unsigned int testyGlobal;
	static unsigned int fatalErrorGlobal;
	static string modulName;
	
	static void startTest();
	static void endTest();
	
	static void startTestModul(string name);
	static bool assert_false( const Tekst& tPlik, const IdType& iLinia, bool a );
	static bool assert_true( const Tekst& tPlik, const IdType& iLinia, bool a );
	static bool endTestModul();
	static bool endTestModulImidaite();
	/* */

public:

	//Inicjalizacja * init;

	Testy();
	~Testy();
	void run();

	bool test_tworzenieObiektow();
	bool test_KlasaObiektList();
	bool test_KlasaLadownia();
	bool test_KlasaNiepoprawneParametryFunkcji();
	bool test_wymagan();

	//void test_ladowaniePlikuXML();
	//void test_podzialuStatku();
	//void test_metodyToString();
};

