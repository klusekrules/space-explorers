#include "ZapisStanuGryTest.h"


ZapisStanuGryTest::ZapisStanuGryTest(void)
	: p_a(Identyfikator(0))
{
}


void ZapisStanuGryTest::zapis(){
	ptr_a = (int)(&(Aplikacja::pobierzInstancje().pobierzGre()));
	p_a = Aplikacja::pobierzInstancje().pobierzGre().pobierzUzytkownika().pobierzPlanete(Identyfikator(1));
	UNIT_TEST_ASSERT_TRUE(Aplikacja::pobierzInstancje().zapiszGre());
}

void ZapisStanuGryTest::odczyt(){
	UNIT_TEST_ASSERT_TRUE(Aplikacja::pobierzInstancje().wczytajGre());
	Planeta p_b = Aplikacja::pobierzInstancje().pobierzGre().pobierzUzytkownika().pobierzPlanete(Identyfikator(1));
	int ptr_b = (int)(&(Aplikacja::pobierzInstancje().pobierzGre()));
	UNIT_TEST_ASSERT_NOTEQUAL(ptr_a,ptr_b);
	UNIT_TEST_ASSERT_EQUAL(p_a.pobierzIloscTypowObiektow(),p_b.pobierzIloscTypowObiektow());
	UNIT_TEST_ASSERT_EQUAL(p_a.pobierzObiekt(Identyfikator(1)).pobierzIlosc(),p_b.pobierzObiekt(Identyfikator(1)).pobierzIlosc());
}

ZapisStanuGryTest::~ZapisStanuGryTest(void)
{
}
