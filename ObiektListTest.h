#pragma once
#include "TestyJednostkowe.h"
#include "Statek.h"

class ObiektListTest : 
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(ObiektListTest);
		DODAJ_TEST(podstawowyTest);
	TWORZ_PACZKE_TESTOW_END();
public:
	void startTestow() override;
	void podstawowyTest();
	void koniecTestow() override;
	ObiektListTest(void) = default;
	virtual ~ObiektListTest(void) = default;
private:
	SpEx::ListaObiektow<SpEx::Statek> lista;
	SpEx::ListaObiektow<SpEx::Statek> listaDruga;
	
	std::shared_ptr<SpEx::Statek> a;
	std::shared_ptr<SpEx::Statek> b;
	std::shared_ptr<SpEx::Statek> c;
	std::shared_ptr<SpEx::Statek> d;
};

