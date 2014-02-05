#pragma once
#include "TestyJednostkowe.h"
#include "Aplikacja.h"

class ObronaTest: 
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(ObronaTest);
		DODAJ_TEST(Test1);
		DODAJ_TEST(Test2);
		DODAJ_TEST(Test3);
	TWORZ_PACZKE_TESTOW_END();
public:
	void startTestow() override;
	void Test1();
	void Test2();
	void Test3();
	ObronaTest(void) = default;
	virtual ~ObronaTest(void) = default;

private:
	const SpEx::Obrona* a;
	SpEx::Obrona* b;
	std::shared_ptr<SpEx::Planeta> planeta;
};

