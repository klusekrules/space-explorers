#include "InicjalizacjaDanychTestowych.h"
#include "Aplikacja.h"


InicjalizacjaDanychTestowych::InicjalizacjaDanychTestowych(void)
{
}

void InicjalizacjaDanychTestowych::zaladujDane(){
	UNIT_TEST_ASSERT_EQUAL(true,Aplikacja::getInstance().WczytajDane());
}

InicjalizacjaDanychTestowych::~InicjalizacjaDanychTestowych(void)
{
}


