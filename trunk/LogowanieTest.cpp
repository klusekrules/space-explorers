#include "LogowanieTest.h"
#include "Aplikacja.h"
#include "Utils.h"
#include "TestyUtilsBO.h"
#include "SHA3.h"
#include "Gra.h"
#include "definicjeWezlowXML.h"

void LogowanieTest::zaloguj(){
	std::string haslo("haslo");
	SHA3 sha3(haslo);
	haslo = sha3.pobierzNapis();
	
#ifndef LOG_OFF_ALL
	SpEx::Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Info, haslo);
#endif
	if (SpEx::Aplikacja::pobierzInstancje().pobierzGre().nowyGracz("Daniel", haslo)){
#if !(defined(LOG_OFF_ALL) || defined(LOG_OFF_DEBUG))
		SpEx::Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Debug, "U¿ytkownik zosta³ utworzony.");
#endif
	}else{
#if !(defined(LOG_OFF_ALL) || defined(LOG_OFF_DEBUG))
		SpEx::Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Debug, "U¿ytkownik istnieje.");
#endif
	}
	
	auto dokument = TestyUtilsBO::dane();
	UNIT_TEST_ASSERT_NOTNULL(dokument);
	auto root = dokument->pobierzElement(WEZEL_XML_ROOT);
	UNIT_TEST_ASSERT_NOTNULL(root);
	UNIT_TEST_ASSERT_TRUE(SpEx::Aplikacja::pobierzInstancje().wczytajGre(root));
	UNIT_TEST_ASSERT_TRUE(SpEx::Aplikacja::pobierzInstancje().pobierzGre().logowanie("Daniel", haslo));
	//UNIT_TEST_ASSERT_TRUE(Aplikacja::pobierzInstancje().pobierzGre().usunGracza("Daniel",haslo));
}
