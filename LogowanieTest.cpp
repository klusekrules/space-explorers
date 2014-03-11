#include "LogowanieTest.h"
#include "Aplikacja.h"
#include "Utils.h"
#include "TestyUtilsBO.h"

void LogowanieTest::zaloguj(){
	std::string haslo("haslo");
	SpEx::Utils::sha3(haslo);
	SpEx::Aplikacja::pobierzInstancje().pobierzLogger().loguj(SLog::Log::Info, haslo);
	if (SpEx::Aplikacja::pobierzInstancje().pobierzGre().nowyGracz("Daniel", haslo)){
		SpEx::Aplikacja::pobierzInstancje().pobierzLogger().loguj(SLog::Log::Debug, "U¿ytkownik zosta³ utworzony.");
	}else{
		SpEx::Aplikacja::pobierzInstancje().pobierzLogger().loguj(SLog::Log::Debug, "U¿ytkownik istnieje.");
	}

	auto dokument = TestyUtilsBO::dane();
	UNIT_TEST_ASSERT_NOTNULL(dokument);
	auto root = dokument->pobierzElement(WEZEL_XML_ROOT);
	UNIT_TEST_ASSERT_NOTNULL(root);
	UNIT_TEST_ASSERT_TRUE(SpEx::Aplikacja::pobierzInstancje().wczytajGre(root,"Daniel", haslo));
	//UNIT_TEST_ASSERT_TRUE(Aplikacja::pobierzInstancje().pobierzGre().usunGracza("Daniel",haslo));
}
