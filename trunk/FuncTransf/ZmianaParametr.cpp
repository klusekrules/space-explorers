#include "ZmianaParametr.h"
#include "..\Logger\Logger.h"
#include <string>

ZmianaParametr::ZmianaParametr( TiXmlElement* e )
{
	if(e){
		idObiektu = std::stoi(e->Attribute("id"),nullptr,0);
		wspolczynnikObiektu = std::stold(e->Attribute("Wspolczynnik"));
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