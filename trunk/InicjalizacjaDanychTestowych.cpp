#include "InicjalizacjaDanychTestowych.h"
#include "Aplikacja.h"


InicjalizacjaDanychTestowych::InicjalizacjaDanychTestowych(void)
{
}

void InicjalizacjaDanychTestowych::zaladujDane(){
	UNIT_TEST_ASSERT_EQUAL(true,Aplikacja::pobierzInstancje().wczytajDane());
}

InicjalizacjaDanychTestowych::~InicjalizacjaDanychTestowych(void)
{
}


