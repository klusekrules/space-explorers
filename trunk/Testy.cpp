#include "Testy.h"


Testy::Testy(){
	Aplikacja::getInstance();
}

Testy::~Testy(){
}

void Testy::wykonanoTest(){
	++testyGlobal;
}

void Testy::wykrytoBlad(){
	++bledyGlobal;
}
void Testy::wykrytoBladKrytyczny(){
	++fatalErrorGlobal;
}

void Testy::dodajTest(Test &t){
	_tests.push_back(t);
}

void Testy::dodajTest(const string& modul, Test::FunkcjaTestowa funkcjaTestowa , bool czyKrytyczny ){
	Test t( *this, modul, funkcjaTestowa, czyKrytyczny );
	_tests.push_back(t);
}

void Testy::startTest(){
	bledyGlobal=0;
	testyGlobal=0;
	fatalErrorGlobal=0;
	Aplikacja::getInstance().getLog().info("----------------------------------------------");
	Aplikacja::getInstance().getLog().info("              Rozpoczêcie testów               ");
	Aplikacja::getInstance().getLog().info("----------------------------------------------");
	start = chrono::steady_clock::now();
}


void Testy::endTest(){
	stringstream s,t,st;
	end = chrono::steady_clock::now();
	st<<"Czas trwania testów: "<<chrono::duration_cast<chrono::milliseconds>(end - start).count()<< "ms.";
	s<<"Przeprowadzono Testów: "<<testyGlobal<<" , Wykryto B³êdów: "<<bledyGlobal;
	t << "B³êdy krytyczne: " << fatalErrorGlobal;
	Aplikacja::getInstance().getLog().info("----------------------------------------------");
	Aplikacja::getInstance().getLog().info("              Zakoñczenie testów               ");
	Aplikacja::getInstance().getLog().info(s.str());
	Aplikacja::getInstance().getLog().info(t.str());
	Aplikacja::getInstance().getLog().info(st.str());
	Aplikacja::getInstance().getLog().info("----------------------------------------------");
}

void Testy::operator()(){
	startTest();
	for(Test& t : this->_tests ){
		if(!t())
			break;
	}	
	endTest();
}


