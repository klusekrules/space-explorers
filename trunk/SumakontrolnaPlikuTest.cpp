#include "SumakontrolnaPlikuTest.h"
#include "SumaKontrolnaPliku.h"
#pragma warning( disable : 4996 )

#define NAPIS_TESTOWY "TESTTESTTESTTEST"
#define PLIK_TESTOWY "TESTTESTTESTTEST"

void SumaKontrolnaPlikuTest::test()
{
	FILE* fp = fopen(PLIK_TESTOWY, "w");
	UNIT_TEST_ASSERT_NOTNULL(fp);
	fputs(NAPIS_TESTOWY, fp);
	fclose(fp);
	SpEx::SumaKontrolnaPliku sumaKontrolnaPliku(PLIK_TESTOWY);
	SHA3 sha3(NAPIS_TESTOWY);
	UNIT_TEST_ASSERT_EQUAL(sha3.pobierzKontener(),sumaKontrolnaPliku.pobierzSumeKontrolna().pobierzKontener());
	remove(PLIK_TESTOWY);
}
