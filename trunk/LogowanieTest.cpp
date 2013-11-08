#include "LogowanieTest.h"
#include "Aplikacja.h"

#include "Utils.h"

LogowanieTest::LogowanieTest(void)
{
}

void LogowanieTest::zaloguj(){
	string haslo("haslo");
	Utils::sha3(haslo);
	Aplikacja::pobierzInstancje().pobierzLogger().loguj(Log::Info,haslo);
	if(Aplikacja::pobierzInstancje().pobierzGre().nowyGracz("Daniel",haslo)){
		Aplikacja::pobierzInstancje().pobierzLogger().loguj(Log::Debug,"U¿ytkownik zosta³ utworzony.");
	}else{
		Aplikacja::pobierzInstancje().pobierzLogger().loguj(Log::Debug,"U¿ytkownik istnieje.");
	}
	UNIT_TEST_ASSERT_TRUE(Aplikacja::pobierzInstancje().wczytajGre("Daniel",haslo));	
	//UNIT_TEST_ASSERT_TRUE(Aplikacja::pobierzInstancje().pobierzGre().usunGracza("Daniel",haslo));
}

LogowanieTest::~LogowanieTest(void)
{
}

