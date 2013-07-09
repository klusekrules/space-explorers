#include "ZmianaLiniowa.h"
#include "..\Logger\Logger.h"
#include "ZmianaFabryka.h"
#include "..\XmlBO.h"

ZmianaLiniowa::ZmianaLiniowa( TiXmlElement* e )
	: parametr(XmlBO::ZnajdzWezelJezeli<NOTHROW>(e,"Param","id","0"))
{
}

ZmianaLiniowa::~ZmianaLiniowa(void)
{
}

long double ZmianaLiniowa::value(const long double& d, const int& p, const int&) const{
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