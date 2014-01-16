#include <functional> 
#include "LiczenieWymogow.h"
#include "ObiektBazowyInfo.h"

using namespace std::placeholders;
LiczenieWymogow::LiczenieWymogow( Wymagania::Wymog& wymog, Wymagania::PrzetworzoneWymogi& zbiornik, const PodstawoweParametry& parametry )
	: wymog_(wymog), zbiornik_(zbiornik), parametry_(parametry)
{
}

bool LiczenieWymogow::wykonaj(Wymagania::Wymog::TypObiektu obiekt, Wymagania::Wymog::Zmiana zmiana){
	if(!obiekt)
		return false;
	Wymagania::Wymog::TypObiektu kopia;
	if(zmiana)
		kopia = Wymagania::Wymog::TypObiektu ( new Wymagania::TypWymogu( *(obiekt), Poziom( static_cast<Poziom::type_name>(floorl(zmiana->policzWartosc( obiekt->pobierzPoziom()() , static_cast<int>(parametry_.pobierzPoziom()()),parametry_.pobierzIdentyfikatorPlanety()() ))) ) ) );
	else
		kopia = Wymagania::Wymog::TypObiektu ( new Wymagania::TypWymogu( *(obiekt), Poziom( obiekt->pobierzPoziom() ) ) );
	zbiornik_.push_back(kopia);
	return true;
}

bool LiczenieWymogow::operator()(){
	return wymog_.wykonaj(bind(&LiczenieWymogow::wykonaj,this,_1,_2));
}
