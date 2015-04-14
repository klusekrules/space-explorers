#include "ZapisStanuGryTest.h"
#include "TestyUtilsBO.h"

ZapisStanuGryTest::ZapisStanuGryTest(void)
	: p_a(0), ptr_a(0)
{
}

void ZapisStanuGryTest::zapis(){
	std::string haslo("haslo");
	SpEx::Utils::sha3(haslo);
	ptr_a = (int)(&(SpEx::Aplikacja::pobierzInstancje().pobierzGre()));
	p_a = SpEx::Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(STyp::Identyfikator(5))->pobierzObiekt(STyp::Identyfikator(1)).pobierzIlosc();
	UNIT_TEST_ASSERT_TRUE(SpEx::Aplikacja::pobierzInstancje().zapiszGre(std::string("Daniel"), haslo));
}

void ZapisStanuGryTest::odczyt(){
	std::string haslo("haslo");
	SpEx::Utils::sha3(haslo);
	auto dokument = TestyUtilsBO::dane();
	UNIT_TEST_ASSERT_NOTNULL(dokument);
	auto root = dokument->pobierzElement(WEZEL_XML_ROOT);
	UNIT_TEST_ASSERT_NOTNULL(root);
	UNIT_TEST_ASSERT_TRUE(SpEx::Aplikacja::pobierzInstancje().wczytajGre(root));
	STyp::Ilosc p_b = SpEx::Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(STyp::Identyfikator(5))->pobierzObiekt(STyp::Identyfikator(1)).pobierzIlosc();
	int ptr_b = (int)(&(SpEx::Aplikacja::pobierzInstancje().pobierzGre()));
	UNIT_TEST_ASSERT_NOTEQUAL(ptr_a,ptr_b);
	UNIT_TEST_ASSERT_EQUAL(p_a,p_b);
}
