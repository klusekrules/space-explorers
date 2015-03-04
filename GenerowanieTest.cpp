#include "GenerowanieTest.h"
#include "Aplikacja.h"
#include "Gra.h"

void GenerowanieTest::generuj(){
	if (SpEx::Aplikacja::pobierzInstancje().pobierzGre().pobierzIloscGalaktyk() == 0){
		UNIT_TEST_ASSERT_TRUE(SpEx::Aplikacja::pobierzInstancje().pobierzGre().generujNowaGalaktyke());
	}
}