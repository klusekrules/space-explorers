#pragma once
#include "TestyJednostkowe.h"
#include "Aplikacja.h"

class SurowceTest:
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(SurowceTest);
		DODAJ_TEST(TworzenieSurowcaTest);
		DODAJ_TEST(DodawanieSurowcaTest);
	TWORZ_PACZKE_TESTOW_END();
public:
	SurowceTest() = default;
	void TworzenieSurowcaTest();
	void DodawanieSurowcaTest();
	void koniecTestow() override;
	~SurowceTest() = default;
private:
	SpEx::Surowce* krysztal_ = nullptr;
	SpEx::Surowce* krysztal2_ = nullptr;
	SpEx::Surowce* metal_ = nullptr;
};

