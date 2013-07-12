#include "ZmianaPoziomObiektu.h"
#include "XmlBO.h"
#include "Logger.h"
#include "Aplikacja.h"
#include "definicjeWezlowXML.h"

ZmianaPoziomObiektu::ZmianaPoziomObiektu( TiXmlElement* e )
	: parametr_(XmlBO::ZnajdzWezel<NOTHROW>( e, WEZEL_XML_PARAM ))
{
}

ZmianaPoziomObiektu::~ZmianaPoziomObiektu(void)
{
}

long double ZmianaPoziomObiektu::policzWartosc(long double d, int p, int idPlaneta ) const{
	return Aplikacja::getInstance().getGra().getUzytkownik().getPlaneta(Identyfikator(idPlaneta)).pobierzObiekt(Identyfikator(parametr_.pobierzIdentyfikatorObiektu())).getPoziom()();
}

ZmianaPoziomObiektu* ZmianaPoziomObiektu::Kopia()const{
	return new ZmianaPoziomObiektu(*this);
}

bool ZmianaPoziomObiektu::RejestrujZmianaPoziomObiektu(  ZmianaFabryka &ref ){
	return ref.rejestracjaZmiany( identyfikator_, ZmianaPoziomObiektu::TworzZmianaPoziomObiektu );
}

string ZmianaPoziomObiektu::napis()const{
	Logger str(NAZWAKLASY(ZmianaPoziomObiektu));
	str.dodajPole( "Parametr", parametr_ );
	return str.napis();
}

ZmianaInterfejs* ZmianaPoziomObiektu::TworzZmianaPoziomObiektu( TiXmlElement* wezel ){
	return new ZmianaPoziomObiektu(wezel);
}

const int ZmianaPoziomObiektu::identyfikator_(6);

bool RejestrujZmianaPoziomObiektu ( ZmianaFabryka& fabryka , Log& logger ){
	if(ZmianaPoziomObiektu::RejestrujZmianaPoziomObiektu(fabryka))
		logger.info("Zaladowano ZmianaPoziomObiektu.");
	else
		logger.info("Nie zaladowano ZmianaPoziomObiektu.");
	return true;
}
