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
	UNIT_TEST_ASSERT_TRUE(Aplikacja::pobierzInstancje().pobierzGre().nowyGracz("Daniel",haslo));
	UNIT_TEST_ASSERT_TRUE(Aplikacja::pobierzInstancje().pobierzGre().logowanie("Daniel",haslo));
	//UNIT_TEST_ASSERT_TRUE(Aplikacja::pobierzInstancje().pobierzGre().usunGracza("Daniel",haslo));
}

LogowanieTest::~LogowanieTest(void)
{
}

