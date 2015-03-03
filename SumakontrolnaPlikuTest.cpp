#include "SumakontrolnaPlikuTest.h"
#include "SumaKontrolnaPliku.h"
#include "Aplikacja.h"
#pragma warning( disable : 4996 )

#define NAPIS_TESTOWY "TESTTESTTESTTEST"
#define PLIK_TESTOWY "TESTTESTTESTTEST"

void SumaKontrolnaPlikuTest::test()
{
	FILE* fp = fopen(PLIK_TESTOWY, "w");
	UNIT_TEST_ASSERT_NOTNULL(fp);
	fputs(NAPIS_TESTOWY, fp);
	fclose(fp);
	auto sumaKontrolnaPliku = SpEx::Aplikacja::pobierzInstancje().zarzadcaZasobow_.pobierzZasob<SpEx::SumaKontrolnaPliku>(std::string(TYP_ZASOBU_SUMA_KONTROLNA_PLIKU), std::string(PLIK_TESTOWY));
	UNIT_TEST_ASSERT_NOTNULL(sumaKontrolnaPliku);
	SHA3 sha3(NAPIS_TESTOWY);
	UNIT_TEST_ASSERT_EQUAL(sha3.pobierzKontener(),sumaKontrolnaPliku->pobierzSumeKontrolna().pobierzKontener());
	remove(PLIK_TESTOWY);
}
