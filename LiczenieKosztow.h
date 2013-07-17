#pragma once
#include <functional>
#include "Wymagania.h"

class LiczenieKosztow
{
public:
	LiczenieKosztow( Wymagania::Cena&, Wymagania::PrzetworzonaCena& , const Ilosc& , const PodstawoweParametry& );
	~LiczenieKosztow(void);
	bool operator()();
private:
	bool wykonaj(Wymagania::Cena::TypObiektu,Wymagania::Cena::Zmiana);
	Wymagania::Cena& cena;
	Wymagania::PrzetworzonaCena& zbiornik;
	const Ilosc& ilosc;
	const PodstawoweParametry& parametry;
};

