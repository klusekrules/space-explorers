#include "ZapisStanuGryTest.h"
#include "Szkielet\TestyUtilsBO.h"
#include "Algorytmy\SHA3.h"
#include "Kontroler\Gra.h"
#include "Model\Planeta.h"
#include "Utils\DefinicjeWezlowXML.h"
#include "Kontroler\Aplikacja.h"

ZapisStanuGryTest::ZapisStanuGryTest(void)
	: p_a(0), ptr_a(0)
{
}

void ZapisStanuGryTest::zapis(){
	std::string haslo("haslo");
	SHA3 sha3(haslo);
	ptr_a = reinterpret_cast<unsigned long long>(&(SpEx::Aplikacja::pobierzInstancje().pobierzGre()));
	p_a = SpEx::Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(STyp::Identyfikator(5))->pobierzObiekt<SpEx::Obiekt>(STyp::Identyfikator(1)).pobierzIlosc();
	UNIT_TEST_ASSERT_TRUE(SpEx::Aplikacja::pobierzInstancje().zapiszGre());
}

void ZapisStanuGryTest::odczyt(){
	auto dokument = TestyUtilsBO::dane();
	UNIT_TEST_ASSERT_NOTNULL(dokument);
	auto root = dokument->pobierzElement(WEZEL_XML_ROOT);
	UNIT_TEST_ASSERT_NOTNULL(root);
	UNIT_TEST_ASSERT_TRUE(SpEx::Aplikacja::pobierzInstancje().wczytajGre(root));
	STyp::Ilosc p_b = SpEx::Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(STyp::Identyfikator(5))->pobierzObiekt<SpEx::Obiekt>(STyp::Identyfikator(1)).pobierzIlosc();
	auto ptr_b = reinterpret_cast<unsigned long long>(&(SpEx::Aplikacja::pobierzInstancje().pobierzGre()));
	UNIT_TEST_ASSERT_NOTEQUAL(ptr_a,ptr_b);
	UNIT_TEST_ASSERT_EQUAL(p_a,p_b);
}
