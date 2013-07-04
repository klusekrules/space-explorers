#include "ZmianaPotegowaAlt.h"
#include "..\Logger\Logger.h"
#include "ZmianaFabryka.h"
#include "..\XmlBO.h"

ZmianaPotegowaAlt::ZmianaPotegowaAlt( const ticpp::Element * e ) throw(int)
	: wspolczynnik(XmlBO::IterateChildrenElement<NOTHROW>(e,"Param")), wykladnik(nullptr)
{
	if(zFabryka)
		wykladnik=zFabryka->Tworz(XmlBO::IterateChildrenElement<NOTHROW>(e,"Zmiana"));
}

ZmianaPotegowaAlt::~ZmianaPotegowaAlt(void)
{
}

long double ZmianaPotegowaAlt::value(const long double& d, const int& p, const int& i) const{
	if(wykladnik)
		return d * pow(static_cast<long double>(wspolczynnik.getWspolczynnik()),-(wykladnik->value(d,p,i)));
	else
		return d * pow(static_cast<long double>(wspolczynnik.getWspolczynnik()),0);
}

ZmianaPotegowaAlt* ZmianaPotegowaAlt::Kopia()const{
	return new ZmianaPotegowaAlt(*this);
}

bool ZmianaPotegowaAlt::RejestrujZmianaPotegowaAlt( ZmianaFabryka &ref ){
	zFabryka = &ref;
	return ref.RejestracjaZmiany(idKlasy,ZmianaPotegowaAlt::TworzZmianaPotegowaAlt);
}

string ZmianaPotegowaAlt::toString()const{
	Logger str(CLASSNAME(ZmianaPotegowaAlt));
	str.addField("wspolczynnik",wspolczynnik);
	if(wykladnik)
		str.addField("wykladnik",*wykladnik);
	return str.toString();
}
