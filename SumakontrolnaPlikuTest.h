#pragma once
#include "TestyJednostkowe.h"

class SumaKontrolnaPlikuTest :
	public PaczkaTestow
{
	TWORZ_PACZKE_TESTOW(SumaKontrolnaPlikuTest);
		DODAJ_TEST(test);
	TWORZ_PACZKE_TESTOW_END();
public:
	SumaKontrolnaPlikuTest() = default;
	void test();
	virtual ~SumaKontrolnaPlikuTest() = default;
};

