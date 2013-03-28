#include "ZmianaLiniowa.h"
#include "Logger.h"
#include "ZmianaFabryka.h"
#include "XmlBO.h"

ZmianaLiniowa::ZmianaLiniowa( const ticpp::Element* e )
	: parametr(XmlBO::IterateChildrenElement(e,"Parametr"))
{
}

ZmianaLiniowa::~ZmianaLiniowa(void)
{
}

long double ZmianaLiniowa::value(const long double& d) const{
	return d * parametr.getWspolczynnik().value();
}

ZmianaLiniowa* ZmianaLiniowa::Kopia()const{
	return new ZmianaLiniowa(*this);
}

bool ZmianaLiniowa::RejestrujZmianaLiniowa(){
	return ZmianaFabryka::pobierzInstancje().RejestracjaZmiany(idKlasy,ZmianaLiniowa::TworzZmianaLiniowa);
}

string ZmianaLiniowa::toString()const{
	Logger str(LogZmianaLiniowa::className());
	str.addClass(ZmianaInterfejs::toString());
	str.addField("Parametr",parametr);
	return str.toString();
}