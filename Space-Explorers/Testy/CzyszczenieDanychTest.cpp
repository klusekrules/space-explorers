#include "CzyszczenieDanychTest.h"
#include "Kontroler\Aplikacja.h"


CzyszczenieDanychTest::CzyszczenieDanychTest(void)
{
}

void CzyszczenieDanychTest::czysc(){
	SpEx::Aplikacja::pobierzInstancje().nowaGra();
}

CzyszczenieDanychTest::~CzyszczenieDanychTest(void)
{
}
