#include "ZapisStanuGryTest.h"


ZapisStanuGryTest::ZapisStanuGryTest(void)
	: p_a(Identyfikator(0))
{
}


void ZapisStanuGryTest::zapis(){
	ptr_a = (int)(&(Aplikacja::getInstance().getGra()));
	p_a = Aplikacja::getInstance().getGra().getUzytkownik().getPlaneta(Identyfikator(1));
	UNIT_TEST_ASSERT_TRUE(Aplikacja::getInstance().ZapiszGre());
}

void ZapisStanuGryTest::odczyt(){
	UNIT_TEST_ASSERT_TRUE(Aplikacja::getInstance().WczytajGre());
	Planeta p_b = Aplikacja::getInstance().getGra().getUzytkownik().getPlaneta(Identyfikator(1));
	int ptr_b = (int)(&(Aplikacja::getInstance().getGra()));
	UNIT_TEST_ASSERT_NOTEQUAL(ptr_a,ptr_b);
	UNIT_TEST_ASSERT_EQUAL(p_a.pobierzIloscTypowObiektow(),p_b.pobierzIloscTypowObiektow());
	UNIT_TEST_ASSERT_EQUAL(p_a.pobierzObiekt(Identyfikator(1)).getIlosc(),p_b.pobierzObiekt(Identyfikator(1)).getIlosc());
}

ZapisStanuGryTest::~ZapisStanuGryTest(void)
{
}
