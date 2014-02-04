#include "InicjalizacjaDanychTestowych.h"
#include "Aplikacja.h"

void InicjalizacjaDanychTestowych::zaladujDane(){
	UNIT_TEST_ASSERT_TRUE(SpEx::Aplikacja::pobierzInstancje().wczytajDane());
}
