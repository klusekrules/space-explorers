#pragma once

#include "Main.h"
#include "Tekst.h"
#include "Ilosc.h"
#include <chrono>
#include <functional>
using namespace std;
class Testy;

class Test
{
	friend class Testy;
public:
	typedef function< bool( Test& )> FunkcjaTestowa;
	~Test();

	bool assert_false( const Tekst& tPlik, const Ilosc& iLinia, bool a );
	bool assert_true( const Tekst& tPlik, const Ilosc& iLinia, bool a );
	
private:
	Test( Testy& t, const string& modul, FunkcjaTestowa funkcjaTestowa , bool czyKrytyczny );

	bool operator()();
	
	void wykonanoTest();
	void wykrytoBlad();
	void wykrytoBladKrytyczny();

	void startTestModul();
	void endTestModul();
	bool endTestModulImidaite();

	unsigned int uBledy;
	unsigned int uTesty;
	unsigned int uFatalError;

	bool krytyczny;
	FunkcjaTestowa funkcja;
	Testy& testy;
	string modul;
		
	chrono::steady_clock::time_point startlocal;
	chrono::steady_clock::time_point endlocal;
};

