#include <functional> 
#include "LiczenieKosztow.h"
#include "Surowce.h"

using namespace std::placeholders;
LiczenieKosztow::LiczenieKosztow( Wymagania::Cena& o, Wymagania::PrzetworzonaCena& c , const Ilosc& i, const PodstawoweParametry& p )
	: cena(o), zbiornik(c), ilosc(i), parametry(p)
{
}

bool LiczenieKosztow::wykonaj(Wymagania::Cena::TypObiektu obiekt ,Wymagania::Cena::Zmiana zmiana){
	if(!obiekt)
		return false;
	Wymagania::Cena::TypObiektu kopia = Wymagania::Cena::TypObiektu(obiekt->Kopia());
	kopia->ustawKontekst(parametry);
	if(zmiana)
		kopia->setIlosc(Ilosc(ilosc()*zmiana->policzWartosc(obiekt->getIlosc()(),static_cast<int>(parametry.getPoziom()()),parametry.getIdPlanety()())));
	else
		kopia->setIlosc(Ilosc(ilosc()*obiekt->getIlosc()() ));
	zbiornik.push_back(kopia);
	return true;				
}

bool LiczenieKosztow::operator()(){
	return cena.wykonaj(bind(&LiczenieKosztow::wykonaj,this,_1,_2));
}

LiczenieKosztow::~LiczenieKosztow(void)
{
}
