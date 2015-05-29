#include "LogowanieTest.h"
#include "Kontroler\Aplikacja.h"
#include "Utils\Utils.h"
#include "Szkielet\TestyUtilsBO.h"
#include "Algorytmy\SHA3.h"
#include "Algorytmy\Hex.h"
#include "Kontroler\Gra.h"
#include "Utils\DefinicjeWezlowXML.h"

void LogowanieTest::zaloguj(){
	std::string haslo("haslo");
	SHA3 sha3(haslo);
	haslo = sha3.pobierzNapis<Hex>();
	
#ifndef LOG_OFF_ALL
	SpEx::Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Debug, haslo);
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
