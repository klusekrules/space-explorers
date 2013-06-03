#include "ZmianaLiniowa.h"
#include "..\Logger\Logger.h"
#include "ZmianaFabryka.h"
#include "..\XmlBO.h"

ZmianaLiniowa::ZmianaLiniowa( const ticpp::Element* e )
	: parametr(XmlBO::IterateChildrenElement<NOTHROW>(e,"Param"))
{
}

ZmianaLiniowa::~ZmianaLiniowa(void)
{
}

long double ZmianaLiniowa::value(const long double& d, const int& p) const{
	return d * parametr.getWspolczynnik() * p;
}

ZmianaLiniowa* ZmianaLiniowa::Kopia()const{
	return new ZmianaLiniowa(*this);
}

bool ZmianaLiniowa::RejestrujZmianaLiniowa(  ZmianaFabryka &ref ){
	return ref.RejestracjaZmiany(idKlasy,ZmianaLiniowa::TworzZmianaLiniowa);
}

string ZmianaLiniowa::toString()const{
	Logger str(CLASSNAME(ZmianaLiniowa));
	str.addField("Parametr",parametr);
	return str.toString();
}