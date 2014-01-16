#include <functional> 
#include "LiczenieKosztow.h"
#include "Surowce.h"

using namespace std::placeholders;
LiczenieKosztow::LiczenieKosztow( Wymagania::Cena& cena, Wymagania::PrzetworzonaCena& zbiornik , const Ilosc& ilosc, const PodstawoweParametry& parametry )
	: cena_(cena), zbiornik_(zbiornik), ilosc_(ilosc), parametry_(parametry)
{
}

bool LiczenieKosztow::wykonaj(Wymagania::Cena::TypObiektu obiekt ,Wymagania::Cena::Zmiana zmiana){
	if(!obiekt)
		return false;
	Wymagania::Cena::TypObiektu kopia = Wymagania::Cena::TypObiektu(obiekt->kopia());
	kopia->ustawKontekst(parametry_);
	if(zmiana)
		kopia->ustawIlosc(Ilosc(ilosc_()*zmiana->policzWartosc(obiekt->pobierzIlosc()(),static_cast<int>(parametry_.pobierzPoziom()()),parametry_.pobierzIdentyfikatorPlanety()())));
	else
		kopia->ustawIlosc(Ilosc(ilosc_()*obiekt->pobierzIlosc()() ));
	zbiornik_.push_back(kopia);
	return true;				
}

bool LiczenieKosztow::operator()(){
	return cena_.wykonaj(bind(&LiczenieKosztow::wykonaj,this,_1,_2));
}
