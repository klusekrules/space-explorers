#include "ZapisStanuGryTest.h"


ZapisStanuGryTest::ZapisStanuGryTest(void)
: p_a(STyp::Identyfikator(0), STyp::Identyfikator(0))
{
}

void ZapisStanuGryTest::zapis(){
	std::string haslo("haslo");
	SpEx::Utils::sha3(haslo);
	ptr_a = (int)(&(SpEx::Aplikacja::pobierzInstancje().pobierzGre()));
	p_a = SpEx::Aplikacja::pobierzInstancje().pobierzGre().pobierzUzytkownika().pobierzPlanete(STyp::Identyfikator(1));
	UNIT_TEST_ASSERT_TRUE(SpEx::Aplikacja::pobierzInstancje().zapiszGre(std::string("Daniel"), haslo));
}

void ZapisStanuGryTest::odczyt(){
	std::string haslo("haslo");
	SpEx::Utils::sha3(haslo);
	UNIT_TEST_ASSERT_TRUE(SpEx::Aplikacja::pobierzInstancje().wczytajGre(std::string("Daniel"), haslo));
	SpEx::Planeta p_b = SpEx::Aplikacja::pobierzInstancje().pobierzGre().pobierzUzytkownika().pobierzPlanete(STyp::Identyfikator(1));
	int ptr_b = (int)(&(SpEx::Aplikacja::pobierzInstancje().pobierzGre()));
	UNIT_TEST_ASSERT_NOTEQUAL(ptr_a,ptr_b);
	UNIT_TEST_ASSERT_EQUAL(p_a.pobierzIloscTypowObiektow(),p_b.pobierzIloscTypowObiektow());
	//Aplikacja::pobierzInstancje().pobierzLogger().info(p_a.pobierzObiekt(Identyfikator(1)).pobierzIlosc());
	//Aplikacja::pobierzInstancje().pobierzLogger().info(p_b.pobierzObiekt(Identyfikator(1)).pobierzIlosc());
	UNIT_TEST_ASSERT_EQUAL(p_a.pobierzObiekt(STyp::Identyfikator(1)).pobierzIlosc(), p_b.pobierzObiekt(STyp::Identyfikator(1)).pobierzIlosc());
}
