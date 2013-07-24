#include "ZmianaParametr.h"
#include "..\Logger\Logger.h"
#include <string>
#include "..\definicjeWezlowXML.h"
#include "..\XmlBO.h"

ZmianaParametr::ZmianaParametr( TiXmlElement* e )
{
	idObiektu_ = XmlBO::WczytajAtrybut<int>(e,ATRYBUT_XML_IDENTYFIKATOR, 0);
	wspolczynnikObiektu_ = XmlBO::WczytajAtrybut<long double>(e,ATRYBUT_XML_WSPOLCZYNNIK, 0);
}


ZmianaParametr::~ZmianaParametr()
{
}

int ZmianaParametr::pobierzIdentyfikatorObiektu()const{
	return idObiektu_;
}

long double ZmianaParametr::pobierzWspolczynnik()const{
	return wspolczynnikObiektu_;
}

string ZmianaParametr::napis()const{
	Logger str(NAZWAKLASY(ZmianaParametr));
	str.dodajPole("IdObiektu",Logger::tworzPole(idObiektu_));
	str.dodajPole("Parametr",Logger::tworzPole(wspolczynnikObiektu_));
	return str.napis();
}
