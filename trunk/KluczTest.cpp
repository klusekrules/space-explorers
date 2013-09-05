#include "KluczTest.h"
#include "Klucz.h"

KluczTest::KluczTest(void)
{
}

KluczTest::~KluczTest(void)
{
}

void KluczTest::klucz(){
	Identyfikator id(0xffc);
	Poziom poz(14);
	Klucz k(id,poz);
	UNIT_TEST_ASSERT_EQUAL(k.pobierzIdentyfikator(),id);
	UNIT_TEST_ASSERT_EQUAL(k.pobierzPoziom(),poz);
}
