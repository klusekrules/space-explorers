#include "LogowanieTest.h"
#include "Aplikacja.h"

#include "Utils.h"

void LogowanieTest::zaloguj(){
	std::string haslo("haslo");
	SpEx::Utils::sha3(haslo);
	SpEx::Aplikacja::pobierzInstancje().pobierzLogger().loguj(SLog::Log::Info, haslo);
	if (SpEx::Aplikacja::pobierzInstancje().pobierzGre().nowyGracz("Daniel", haslo)){
		SpEx::Aplikacja::pobierzInstancje().pobierzLogger().loguj(SLog::Log::Debug, "U¿ytkownik zosta³ utworzony.");
	}else{
		SpEx::Aplikacja::pobierzInstancje().pobierzLogger().loguj(SLog::Log::Debug, "U¿ytkownik istnieje.");
	}
	UNIT_TEST_ASSERT_TRUE(SpEx::Aplikacja::pobierzInstancje().wczytajGre("Daniel", haslo));
	//UNIT_TEST_ASSERT_TRUE(Aplikacja::pobierzInstancje().pobierzGre().usunGracza("Daniel",haslo));
}
