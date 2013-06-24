#pragma once
#include "Main.h"
#include "Biblioteki.h"
#include "ObiektList.hpp"
#include "StatekInfo.h"
#include "SurowceInfo.h"
#include "Aplikacja.h"
#include "Test.h"
#include <chrono>
#include <vector>

using namespace std;

class Testy
{
	friend class Test;
protected:
	vector<Test> _tests;

	unsigned int bledyGlobal;
	unsigned int testyGlobal;
	unsigned int fatalErrorGlobal;
	chrono::steady_clock::time_point start;
	chrono::steady_clock::time_point end;
	
	void startTest();
	void endTest();

	void wykonanoTest();
	void wykrytoBlad();
	void wykrytoBladKrytyczny();

public:
	Testy();
	~Testy();
	void operator()();
	void dodajTest(Test &t);
	void dodajTest(const string& modul, Test::FunkcjaTestowa funkcjaTestowa , bool czyKrytyczny );
};

