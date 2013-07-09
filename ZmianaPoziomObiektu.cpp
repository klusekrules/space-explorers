#include "ZmianaPoziomObiektu.h"
#include "XmlBO.h"
#include "Logger.h"
#include "Aplikacja.h"

ZmianaPoziomObiektu::ZmianaPoziomObiektu( TiXmlElement* e )
	: parametr(XmlBO::ZnajdzWezel<NOTHROW>(e,"Param"))
{
}

ZmianaPoziomObiektu::~ZmianaPoziomObiektu(void)
{
}

long double ZmianaPoziomObiektu::value(const long double& d, const int& p, const int& idPlaneta ) const{
	return Aplikacja::getInstance().getGra().getUzytkownik().getPlaneta(IdType(idPlaneta)).pobierzObiekt(IdType(parametr.getIdObiektu())).getPoziom()();
}

ZmianaPoziomObiektu* ZmianaPoziomObiektu::Kopia()const{
	return new ZmianaPoziomObiektu(*this);
}

bool ZmianaPoziomObiektu::RejestrujZmianaPoziomObiektu(  ZmianaFabryka &ref ){
	return ref.RejestracjaZmiany(idKlasy,ZmianaPoziomObiektu::TworzZmianaPoziomObiektu);
}

string ZmianaPoziomObiektu::toString()const{
	Logger str(CLASSNAME(ZmianaPoziomObiektu));
	str.addField("Parametr",parametr);
	return str.toString();
}

const int ZmianaPoziomObiektu::idKlasy(6);

bool RejestrujZmianaPoziomObiektu ( ZmianaFabryka& fabryka , Log& logger ){
	if(ZmianaPoziomObiektu::RejestrujZmianaPoziomObiektu(fabryka))
		logger.info("Zaladowano ZmianaPoziomObiektu.");
	else
		logger.info("Nie zaladowano ZmianaPoziomObiektu.");
	return true;
}