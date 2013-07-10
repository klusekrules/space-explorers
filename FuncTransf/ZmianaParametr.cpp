#include "ZmianaParametr.h"
#include "..\Logger\Logger.h"
#include <string>
#include "..\definicjeWezlowXML.h"
#include "..\XmlBO.h"

ZmianaParametr::ZmianaParametr( TiXmlElement* e )
{
	XmlBO::WczytajAtrybut(e,ATRYBUT_XML_IDENTYFIKATOR,idObiektu_);
	XmlBO::WczytajAtrybut(e,ATRYBUT_XML_WSPOLCZYNNIK,wspolczynnikObiektu_);
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

string ZmianaParametr::toString()const{
	Logger str(CLASSNAME(ZmianaParametr));
	str.addField("IdObiektu",Logger::field(idObiektu_));
	str.addField("Parametr",Logger::field(wspolczynnikObiektu_));
	return str.toString();
}