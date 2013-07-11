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
	return Aplikacja::getInstance().getGra().getUzytkownik().getPlaneta(IdType(idPlaneta)).pobierzObiekt(IdType(parametr_.pobierzIdentyfikatorObiektu())).getPoziom()();
}

ZmianaPoziomObiektu* ZmianaPoziomObiektu::Kopia()const{
	return new ZmianaPoziomObiektu(*this);
}

bool ZmianaPoziomObiektu::RejestrujZmianaPoziomObiektu(  ZmianaFabryka &ref ){
	return ref.rejestracjaZmiany( identyfikator_, ZmianaPoziomObiektu::TworzZmianaPoziomObiektu );
}

string ZmianaPoziomObiektu::toString()const{
	Logger str(CLASSNAME(ZmianaPoziomObiektu));
	str.addField( "Parametr", parametr_ );
	return str.toString();
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
