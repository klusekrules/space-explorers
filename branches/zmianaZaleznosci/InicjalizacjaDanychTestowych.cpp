#include "InicjalizacjaDanychTestowych.h"
#include "Aplikacja.h"
#include "TestyUtilsBO.h"

void InicjalizacjaDanychTestowych::zaladujDane(){
	auto dokument = TestyUtilsBO::dane();
	UNIT_TEST_ASSERT_NOTNULL(dokument);
	dokument->zapisz("danetestowe.xml");
	auto root = dokument->pobierzElement(WEZEL_XML_ROOT);
	UNIT_TEST_ASSERT_NOTNULL(root);
	UNIT_TEST_ASSERT_TRUE(SpEx::Aplikacja::pobierzInstancje().wczytajDane(root));
}
