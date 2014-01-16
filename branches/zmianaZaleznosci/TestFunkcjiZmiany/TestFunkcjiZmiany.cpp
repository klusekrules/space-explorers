#include "TestFunkcjiZmiany.h"
#include "..\XmlBO.h"
#include "..\Logger.h"
#include "..\definicjeWezlowXML.h"

ZmianaTest::ZmianaTest( tinyxml2::XMLElement* e )
	: parametr_(XmlBO::ZnajdzWezel<NOTHROW>( e, WEZEL_XML_PARAM ))
{
}

ZmianaTest::~ZmianaTest(void)
{
}

ZmianaInterfejs* ZmianaTest::TworzZmianaTest( tinyxml2::XMLElement* wezel ){
	return new ZmianaTest(wezel);
}


long double ZmianaTest::policzWartosc(long double wartosc, int poziom, int identyfikatorPlanety) const{
	return wartosc * parametr_.pobierzWspolczynnik() * poziom * 10 ;
}

ZmianaTest* ZmianaTest::Kopia()const{
	return new ZmianaTest(*this);
}

bool ZmianaTest::RejestrujZmianaTest(  ZmianaFabryka &ref ){
	return ref.rejestracjaZmiany( identyfikator_, ZmianaTest::TworzZmianaTest );
}

std::string ZmianaTest::napis()const{
	Logger str(NAZWAKLASY(ZmianaTest));
	str.dodajPole( "Parametr", parametr_ );
	return str.napis();
}

const int ZmianaTest::identyfikator_(5);

bool RejestrujZmiany ( ZmianaFabryka& fabryka , Log& logger ){
	if(ZmianaTest::RejestrujZmianaTest(fabryka))
		logger.loguj(Log::Info,"Zaladowano ZmianaTest.");
	else
		logger.loguj(Log::Info,"Nie zaladowano ZmianaTest.");
	return true;
}
