#include "ZmianaParametr.h"
#include "Logger.h"


ZmianaParametr::ZmianaParametr( const ticpp::Element* e )
{
	if(e){
		idObiektu.setId(stoi(e->GetAttribute("id"),nullptr,0));
		auto str = e->GetAttribute("Wspolczynnik");
		wspolczynnikObiektu.setParametr(stold(str));
	}
}


ZmianaParametr::~ZmianaParametr()
{
}

string ZmianaParametr::toString()const{
	Logger str(className());
	str.addField("IdObiektu",idObiektu);
	str.addField("Parametr",wspolczynnikObiektu);
	return str.toString();
}