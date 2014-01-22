#include "TestFunkcjiZmiany.h"
#include "Zmiana\ZmianaStaleXml.h"
#include "Logger\Logger.h"
#include "TypyProste\TypyProsteBO.h"
#include "TestFunkcjiZmianyStale.h"

namespace SZmi{
	ZmianaTest::ZmianaTest(XmlBO::ElementWezla e)
		: parametr_(XmlBO::ZnajdzWezel<NOTHROW>(e, XML_WEZEL_ZMIANA_PARAM))
	{
	}
	
	ZmianaInterfejs* ZmianaTest::TworzZmianaTest(XmlBO::ElementWezla wezel){
		return new ZmianaTest(wezel);
	}

	STyp::Wartosc ZmianaTest::policzWartosc(const STyp::Wartosc& wartosc, const STyp::Poziom& poziom, const STyp::Identyfikator& identyfikatorPlanety) const{
		return STyp::pomnozWartosc( wartosc * parametr_.pobierzWspolczynnik() , poziom ) * 10;
	}

	ZmianaTest* ZmianaTest::Kopia()const{
		return new ZmianaTest(*this);
	}

	bool ZmianaTest::RejestrujZmianaTest(ZmianaFabryka &ref){
		return ref.rejestracjaZmiany(identyfikator_, ZmianaTest::TworzZmianaTest);
	}

	std::string ZmianaTest::napis()const{
		SLog::Logger str(NAZWAKLASY(ZmianaTest));
		str.dodajPole(NAZWAPOLA(parametr_), parametr_);
		return str.napis();
	}

	const int ZmianaTest::identyfikator_(5);
}

bool RejestrujZmiany(SZmi::ZmianaFabryka& fabryka, SLog::Log& logger){
	if (SZmi::ZmianaTest::RejestrujZmianaTest(fabryka))
		logger.loguj(SLog::Log::Info, TEST_FUNKCJI_ZMIANY_ZALADOWANO);
	else
		logger.loguj(SLog::Log::Info, TEST_FUNKCJI_ZMIANY_NIE_ZALADOWANO);
	return true;
}

