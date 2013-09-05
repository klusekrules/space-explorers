#include "Wymagania.h"
#include "Logger.h"
#include "Aplikacja.h"
#include "XmlBO.h"
#include "definicjeWezlowXML.h"
#include "LiczenieKosztow.h"
#include "LiczenieWymogow.h"
using namespace std::placeholders;
Wymagania::Wymagania( TiXmlElement* wezel  )
{
	if(wezel){
		try{
			auto wymog = wezel->FirstChildElement(WEZEL_XML_WYMOG);
			while(wymog){
				auto obiekt = Wymog(wymog,WEZEL_XML_OBIEKTBASE_INFO);
				auto identyfikator = obiekt.pobierzObiekt()->pobierzIdentyfikator();
				for(auto element : warunki_ ){
					if(element.pobierzObiekt()->pobierzIdentyfikator() == identyfikator)
						Utils::generujWyjatekBleduStruktury(EXCEPTION_PLACE,wymog);
				}
				warunki_.push_back(obiekt);					
				wymog = wymog->NextSiblingElement(WEZEL_XML_WYMOG);
			}

			auto zmiana = XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel->FirstChildElement(WEZEL_XML_CZAS),WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,WEZEL_XML_CZAS);
			if(zmiana)
				zmianaCzasuBudowy_=Utils::TworzZmiane(zmiana);
			auto cena = wezel->FirstChildElement(WEZEL_XML_CENA);
			while(cena){
				auto obiekt = Cena(cena,WEZEL_XML_SUROWCE,std::bind(&Gra::tworzSurowce,&(Aplikacja::pobierzInstancje().pobierzGre()),_1));
				auto identyfikator = obiekt.pobierzObiekt()->pobierzIdentyfikator();
				for(auto element : koszty_ ){
					if(element.pobierzObiekt()->pobierzIdentyfikator() == identyfikator)
						Utils::generujWyjatekBleduStruktury(EXCEPTION_PLACE,cena);
				}
				koszty_.push_back(obiekt);					
				cena = cena->NextSiblingElement(WEZEL_XML_CENA);
			}
		}catch(exception& wyjatek){
			throw WyjatekParseraXML(EXCEPTION_PLACE,wyjatek,WyjatekParseraXML::trescBladStrukturyXml);
		}

	}
}

Wymagania::~Wymagania(){
}

Czas Wymagania::pobierzCzasBudowy( const Ilosc& ilosc, const PodstawoweParametry& parametry )const{
	auto koszty = pobierzKoszty(ilosc,parametry);
	Czas suma(0.0l);
	for( auto element : koszty ){
		if(element)
			suma+=element->pobierzCzas();
	}
	if(zmianaCzasuBudowy_){		
		suma = zmianaCzasuBudowy_->policzWartosc(suma(),static_cast<int>(parametry.pobierzPoziom()()),parametry.pobierzIdentyfikatorPlanety()());
	}
	return suma;
}

bool Wymagania::czySpelniaWymagania( const Ilosc& ilosc, const PodstawoweParametry& parametry ) const{
	return czySpelniaKoszty(ilosc,parametry) && czySpelniaWymogi(parametry);
}

bool Wymagania::czySpelniaWymogi( const PodstawoweParametry& parametry ) const{	
	if(warunki_.empty())
		return true;
	shared_ptr<Planeta> planeta = Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(parametry.pobierzIdentyfikatorPlanety());
	if(!planeta){
		return false;
	}
	for (auto element : warunki_){
		Poziom poziom;
		if(element.wykonaj(
			[&](Wymog::TypObiektu obiekt,Wymog::Zmiana zmiana)->bool{
				if (!obiekt)
					return false;
				if(zmiana)
					poziom = Poziom(static_cast<Poziom::type_name>(zmiana->policzWartosc(obiekt->pobierzPoziom()(),parametry.pobierzPoziom()(),parametry.pobierzIdentyfikatorPlanety()())));
				else
					poziom = obiekt->pobierzPoziom();
				return true;
		}			
		))
		{
			if(planeta->pobierzObiekt(element.pobierzObiekt()->pobierzIdentyfikator()).pobierzPoziom()<poziom)
				return false;
		}
	}
	return true;
}

bool Wymagania::czySpelniaKoszty( const Ilosc& ilosc, const PodstawoweParametry& parametry ) const{
	if(koszty_.empty())
		return true;
	shared_ptr<Planeta> planeta = Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(parametry.pobierzIdentyfikatorPlanety());
	if(!planeta){
		return false;
	}
	for( auto element : koszty_ ){
		Ilosc iloscObiektow;
		if(element.wykonaj(
			[&](Cena::TypObiektu obiekt,Cena::Zmiana zmiana)->bool{
				if (!obiekt)
					return false;
				if(zmiana)
					iloscObiektow = Ilosc(static_cast<Ilosc::type_name>(zmiana->policzWartosc(obiekt->pobierzIlosc()(),parametry.pobierzPoziom()(),parametry.pobierzIdentyfikatorPlanety()())));
				else
					iloscObiektow = obiekt->pobierzIlosc();
				return true;
		}			
		))
		{
			if( planeta->pobierzObiekt(element.pobierzObiekt()->ID()).pobierzIlosc() < (iloscObiektow*ilosc ) )
				return false;
		}
	}
	return true;
}

Wymagania::PrzetworzoneWymogi Wymagania::pobierzWymogi( const PodstawoweParametry& parametry ) const{
	PrzetworzoneWymogi zbiornik;
	for (auto element : warunki_){
		LiczenieWymogow(element,zbiornik,parametry)();
	}
	return zbiornik;
}

Wymagania::PrzetworzonaCena Wymagania::pobierzKoszty( const Ilosc& ilosc, const PodstawoweParametry& parametry ) const{
	PrzetworzonaCena zbiornik;
	for( auto element : koszty_ ){
		LiczenieKosztow (element,zbiornik,ilosc,parametry)();
	}
	return zbiornik;
}

string Wymagania::napis() const{
	Logger str(NAZWAKLASY(Wymagania));

	str.rozpocznijPodKlase("ListaCen");
	for(auto element : koszty_){
		str.rozpocznijPodKlase(NAZWAKLASY(Wymagania::Cena));
		if(element.pobierzObiekt())
			str.dodajPole("Obiekt",*element.pobierzObiekt());
		if(element.pobierzZmiane())
			str.dodajPole("Zmiana",*element.pobierzZmiane());
		str.zakonczPodKlase();
	}
	str.zakonczPodKlase();

	str.rozpocznijPodKlase("ListaWymogów");
	for(auto element : warunki_){
		str.rozpocznijPodKlase(NAZWAKLASY(Wymagania::Wymog));
		if(element.pobierzObiekt())
			str.dodajPole("Obiekt",*element.pobierzObiekt());
		if(element.pobierzZmiane())
			str.dodajPole("Zmiana",*element.pobierzZmiane());
		str.zakonczPodKlase();
	}
	str.zakonczPodKlase();

	if(zmianaCzasuBudowy_)
		str.dodajPole("ZmianaCzasuBudowy",*zmianaCzasuBudowy_);

	return str.napis();
}
