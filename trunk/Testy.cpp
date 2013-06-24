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
	Aplikacja::getInstance().getLog().info("              Rozpocz�cie test�w               ");
	Aplikacja::getInstance().getLog().info("----------------------------------------------");
	start = chrono::steady_clock::now();
}


void Testy::endTest(){
	stringstream s,t,st;
	end = chrono::steady_clock::now();
	st<<"Czas trwania test�w: "<<chrono::duration_cast<chrono::milliseconds>(end - start).count()<< "ms.";
	s<<"Przeprowadzono Test�w: "<<testyGlobal<<" , Wykryto B��d�w: "<<bledyGlobal;
	t << "B��dy krytyczne: " << fatalErrorGlobal;
	Aplikacja::getInstance().getLog().info("----------------------------------------------");
	Aplikacja::getInstance().getLog().info("              Zako�czenie test�w               ");
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


