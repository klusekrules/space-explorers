#pragma once
#include "Main.h"
#include "Biblioteki.h"
#include "ObiektList.hpp"
#include "StatekInfo.h"
#include "SurowceInfo.h"

class Testy
{
private:
	hash_map<IdType,StatekInfo*> statki;
	bool setStatek(StatekInfo* statek);
	StatekInfo& getStatek(const IdType& id)const throw (NieznalezionoObiektu);
	Statek* tworzStatek(const IdType& id,const Ilosc& i)const throw (OgolnyWyjatek,NieznalezionoObiektu);

	hash_map<IdType,SurowceInfo*> surowce;
	bool setSurowce(SurowceInfo* surowiec);
	SurowceInfo& getSurowce(const IdType& id)const throw (NieznalezionoObiektu);
	Surowce* tworzSurowce(const IdType& id,const Ilosc& i)const throw (OgolnyWyjatek,NieznalezionoObiektu);


	bool ladowanie_danych();

	/* */
	static unsigned int bledy;
	static unsigned int testy;
	static unsigned int bledyGlobal;
	static unsigned int testyGlobal;
	static string modulName;
	
	static void startTest();
	static void endTest();
	static void startTestModul(string name);
	static bool assert_false( const Tekst& tPlik, const IdType& iLinia, bool a );
	static bool assert_true( const Tekst& tPlik, const IdType& iLinia, bool a );
	static bool endTestModul();
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

	//void test_ladowaniePlikuXML();
	//void test_podzialuStatku();
	//void test_metodyToString();
};

