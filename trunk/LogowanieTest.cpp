#include "LogowanieTest.h"
#include "Aplikacja.h"

#include "Utils.h"

LogowanieTest::LogowanieTest(void)
{
}

void LogowanieTest::zaloguj(){
	string haslo("haslo");
	Utils::sha3(haslo);
	Aplikacja::pobierzInstancje().pobierzLogger().info(haslo);
	if(Aplikacja::pobierzInstancje().pobierzGre().nowyGracz("Daniel",haslo)){
		Aplikacja::pobierzInstancje().pobierzLogger().debug("U¿ytkownik zosta³ utworzony.");
	}else{
		Aplikacja::pobierzInstancje().pobierzLogger().debug("U¿ytkownik istnieje.");
	}
	UNIT_TEST_ASSERT_TRUE(Aplikacja::pobierzInstancje().wczytajGre("Daniel",haslo));
	Aplikacja::pobierzInstancje().pobierzGre().generujNowaGalaktyke();
	//UNIT_TEST_ASSERT_TRUE(Aplikacja::pobierzInstancje().pobierzGre().usunGracza("Daniel",haslo));
}

LogowanieTest::~LogowanieTest(void)
{
}

