#include "InicjalizacjaDanychTestowych.h"
#include "Aplikacja.h"
#include "TestyUtilsBO.h"

void InicjalizacjaDanychTestowych::zaladujDane(){
	SpEx::Aplikacja::pobierzInstancje().wyczyscDane();
	auto dokument = TestyUtilsBO::dane();
	UNIT_TEST_ASSERT_NOTNULL(dokument);
	if (SpEx::Aplikacja::pobierzInstancje().logger_.czyLogiOdblokowane(SLog::Log::Debug)){
		dokument->zapisz("danetestowe.xml");
	}
	auto root = dokument->pobierzElement(WEZEL_XML_ROOT);
	UNIT_TEST_ASSERT_NOTNULL(root);
	UNIT_TEST_ASSERT_TRUE(SpEx::Aplikacja::pobierzInstancje().wczytajGre(root));
}
