#include "InicjalizacjaDanychTestowych.h"
#include "Aplikacja.h"


InicjalizacjaDanychTestowych::InicjalizacjaDanychTestowych(void)
{
}

void InicjalizacjaDanychTestowych::zaladujDane(){
	UNIT_TEST_ASSERT_TRUE(Aplikacja::pobierzInstancje().wczytajDane());
}

void InicjalizacjaDanychTestowych::generujDane(){
	
}

InicjalizacjaDanychTestowych::~InicjalizacjaDanychTestowych(void)
{
}


