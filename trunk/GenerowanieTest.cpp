#include "GenerowanieTest.h"
#include "Aplikacja.h"


GenerowanieTest::GenerowanieTest(void)
{
}


void GenerowanieTest::generuj(){
	if( Aplikacja::pobierzInstancje().pobierzGre().pobierzIloscGalaktyk() == 0 ){
		UNIT_TEST_ASSERT_TRUE(Aplikacja::pobierzInstancje().pobierzGre().generujNowaGalaktyke());
	}
}

GenerowanieTest::~GenerowanieTest(void)
{
}
