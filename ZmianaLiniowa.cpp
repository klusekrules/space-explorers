#include "ZmianaLiniowa.h"
#include "Logger.h"
#include "ZmianaFabryka.h"
#include "XmlBO.h"

ZmianaLiniowa::ZmianaLiniowa( const ticpp::Element* e )
	: parametr(XmlBO::IterateChildrenElement(e,"Param"))
{
}

ZmianaLiniowa::~ZmianaLiniowa(void)
{
}

long double ZmianaLiniowa::value(const long double& d, const Poziom& p) const{
	return d * parametr.getWspolczynnik().value() * p.value();
}

ZmianaLiniowa* ZmianaLiniowa::Kopia()const{
	return new ZmianaLiniowa(*this);
}

bool ZmianaLiniowa::RejestrujZmianaLiniowa(){
	return ZmianaFabryka::pobierzInstancje().RejestracjaZmiany(idKlasy,ZmianaLiniowa::TworzZmianaLiniowa);
}

string ZmianaLiniowa::toString()const{
	Logger str(LogZmianaLiniowa::className());
	str.addField("Parametr",parametr);
	return str.toString();
}