#include "ZmianaParametr.h"
#include "..\Logger\Logger.h"
#include <string>
#include "..\definicjeWezlowXML.h"

ZmianaParametr::ZmianaParametr( TiXmlElement* e )
{
	if(e){
		idObiektu = std::stoi(e->Attribute(ATRYBUT_XML_IDENTYFIKATOR),nullptr,0);
		wspolczynnikObiektu = std::stold(e->Attribute(ATRYBUT_XML_WSPOLCZYNNIK));
	}
}


ZmianaParametr::~ZmianaParametr()
{
}

string ZmianaParametr::toString()const{
	Logger str(CLASSNAME(ZmianaParametr));
	str.addField("IdObiektu",Logger::field(idObiektu));
	str.addField("Parametr",Logger::field(wspolczynnikObiektu));
	return str.toString();
}