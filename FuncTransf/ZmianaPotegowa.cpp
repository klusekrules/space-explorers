#include "ZmianaPotegowa.h"
#include "..\Logger\Logger.h"
#include "ZmianaFabryka.h"
#include "..\XmlBO.h"

ZmianaPotegowa::ZmianaPotegowa( const ticpp::Element * e ) throw(WyjatekParseraXML)
	: wspolczynnik(XmlBO::IterateChildrenElement(e,"Param1")), wykladnik(XmlBO::IterateChildrenElement(e,"Param2"))
{
}

ZmianaPotegowa::~ZmianaPotegowa(void)
{
}

long double ZmianaPotegowa::value(const long double& d, const int& p) const{
	return d * wspolczynnik.getWspolczynnik() * pow(static_cast<long double>(p),wykladnik.getWspolczynnik());
}

ZmianaPotegowa* ZmianaPotegowa::Kopia()const{
	return new ZmianaPotegowa(*this);
}

bool ZmianaPotegowa::RejestrujZmianaPotegowa(){
	return ZmianaFabryka::pobierzInstancje().RejestracjaZmiany(idKlasy,ZmianaPotegowa::TworzZmianaPotegowa);
}

string ZmianaPotegowa::toString()const{
	Logger str(CLASSNAME(ZmianaPotegowa));
	str.addField("wspolczynnik",wspolczynnik);
	str.addField("wykladnik",wykladnik);
	return str.toString();
}