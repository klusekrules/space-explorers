#include "ZmianaParametr.h"
#include "..\Logger\Logger.h"


ZmianaParametr::ZmianaParametr( const ticpp::Element* e )
{
	if(e){
		idObiektu = stoi(e->GetAttribute("id"),nullptr,0);
		wspolczynnikObiektu = stold(e->GetAttribute("Wspolczynnik"));
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