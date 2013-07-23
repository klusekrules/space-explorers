#pragma once
#include "TestyJednostkowe.h"
#include "Aplikacja.h"

class ObiektListTest : 
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(ObiektListTest);
		DODAJ_TEST(podstawowyTest);
	TWORZ_PACZKE_TESTOW_END();
public:
	void startTestow() override;
	void podstawowyTest();
	ObiektListTest(void);
	virtual ~ObiektListTest(void);
private:
	ListaObiektow<Statek> lista;
	ListaObiektow<Statek> listaDruga;
	
	shared_ptr<Statek> a;
	shared_ptr<Statek> b;
	shared_ptr<Statek> c;
	shared_ptr<Statek> d;
};

