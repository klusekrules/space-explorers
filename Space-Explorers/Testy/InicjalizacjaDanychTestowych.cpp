#include "InicjalizacjaDanychTestowych.h"
#include "Kontroler\Aplikacja.h"
#include "Szkielet\TestyUtilsBO.h"
#include "Utils\DefinicjeWezlowXML.h"

void InicjalizacjaDanychTestowych::zaladujDane(){
	SpEx::Aplikacja::pobierzInstancje().nowaGra();
	auto dokument = TestyUtilsBO::dane();
	UNIT_TEST_ASSERT_NOTNULL(dokument);
	if (SpEx::Aplikacja::pobierzInstancje().logger_.czyLogiOdblokowane(SLog::Log::Debug)){
		dokument->zapisz("danetestowe.xml");
	}
	auto root = dokument->pobierzElement(WEZEL_XML_ROOT);
	UNIT_TEST_ASSERT_NOTNULL(root);
	UNIT_TEST_ASSERT_TRUE(SpEx::Aplikacja::pobierzInstancje().wczytajGre(root));
}
