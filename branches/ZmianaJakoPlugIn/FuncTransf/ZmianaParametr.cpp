#include "ZmianaParametr.h"
#include "../Logger/Logger.h"


ZmianaParametr::ZmianaParametr( const ticpp::Element* e )
{
	if(e){
		idObiektu.setId(stoi(e->GetAttribute("id"),nullptr,0));
		wspolczynnikObiektu.setParametr(stold(e->GetAttribute("Wspolczynnik")));
	}
}


ZmianaParametr::~ZmianaParametr()
{
}

string ZmianaParametr::toString()const{
	Logger str(CLASSNAME(ZmianaParametr));
	str.addField("IdObiektu",idObiektu);
	str.addField("Parametr",wspolczynnikObiektu);
	return str.toString();
}