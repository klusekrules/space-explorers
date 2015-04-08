#include "CzyszczenieDanychTest.h"
#include "Kontroler\Aplikacja.h"


CzyszczenieDanychTest::CzyszczenieDanychTest(void)
{
}

void CzyszczenieDanychTest::czysc(){
	SpEx::Aplikacja::pobierzInstancje().wyczyscDane();
}

CzyszczenieDanychTest::~CzyszczenieDanychTest(void)
{
}
