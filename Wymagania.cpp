#include "Wymagania.h"
#include "Logger.h"
#include "Aplikacja.h"
#include "XmlBO.h"
#include "definicjeWezlowXML.h"
#include "LiczenieKosztow.h"
#include "LiczenieWymogow.h"

Wymagania::Wymagania( TiXmlElement* wezel  )
{
	if(wezel){
		try{
			auto wymog = wezel->FirstChildElement(WEZEL_XML_WYMOG);
			while(wymog){
				dodajWymog(Wymog(wymog,WEZEL_XML_OBIEKTBASE_INFO));
				wymog = wymog->NextSiblingElement(WEZEL_XML_WYMOG);
			}

			auto zmiana = XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel->FirstChildElement(WEZEL_XML_CZAS),WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,WEZEL_XML_CZAS);
			if(zmiana)
				zmianaCzasuBudowy_=Aplikacja::getInstance().getGra().getZmianaFabryka().Tworz(zmiana);
			auto cena = wezel->FirstChildElement(WEZEL_XML_CENA);
			while(cena){
				dodajCene(Cena(cena,WEZEL_XML_SUROWCE));
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
	Czas suma(0);
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

bool Wymagania::dodajWymog( Wymog& wymog ){
	bool zamien = true;
	for(auto element = warunki_.begin() ; element != warunki_.end() ; ++element ){
		if(element->wykonaj(
			[&wymog,&zamien](Wymog::TypObiektu obiekt,Wymog::Zmiana zmiana)->bool{
				if(!obiekt)
					return false;
				auto identyfikator = obiekt->pobierzIdentyfikator();
				auto poziom = obiekt->pobierzPoziom();
				return wymog.wykonaj(
					[&identyfikator,&poziom,&zamien](Wymog::TypObiektu obiekt,Wymog::Zmiana zmiana)->bool{
						if(!obiekt)
							return false;
						if( identyfikator == obiekt->pobierzIdentyfikator() ){
							zamien = ( poziom < obiekt->pobierzPoziom() );
							return true;
						}
						return false;
				}
				);
		}
		)){
			if(zamien){
				warunki_.erase(element);
				warunki_.push_back(wymog);
			}
			return zamien;
		}
	}
	warunki_.push_back(wymog);
	return true;
}

bool Wymagania::dodajCene( Cena& cena ){
	bool zamien = true;
	for(auto element = koszty_.begin() ; element != koszty_.end() ; ++element ){
		if(element->wykonaj(
			[&cena,&zamien](Cena::TypObiektu obiekt,Cena::Zmiana zmiana)->bool{
				if(!obiekt)
					return false;
				auto identyfikator = obiekt->pobierzIdentyfikator();
				auto ilosc = obiekt->getIlosc();
				return cena.wykonaj(
					[&identyfikator,&ilosc,&zamien](Cena::TypObiektu obiekt,Cena::Zmiana zmiana)->bool{
						if(!obiekt)
							return false;
						if( identyfikator == obiekt->pobierzIdentyfikator() ){
							zamien = ( ilosc < obiekt->getIlosc() );
							return true;
						}
						return false;
				}
				);
		}
		)){
			if(zamien){
				koszty_.erase(element);
				koszty_.push_back(cena);
			}
			return zamien;
		}
	}
	koszty_.push_back(cena);
	return true;
}

bool Wymagania::czySpelniaWymogi( const PodstawoweParametry& parametry ) const{	
	if(warunki_.empty())
		return true;
	const Planeta& planeta = Aplikacja::getInstance().getGra().getUzytkownik().getPlaneta(parametry.pobierzIdentyfikatorPlanety());
	for (auto element : warunki_){
		Poziom poziom;
		Identyfikator identyfikator;
		if(element.wykonaj(
			[&parametry,&poziom,&identyfikator](Wymog::TypObiektu obiekt,Wymog::Zmiana zmiana)->bool{
				if (!obiekt)
					return false;
				identyfikator = obiekt->pobierzIdentyfikator();
				if(zmiana)
					poziom = Poziom(static_cast<Poziom::type_name>(zmiana->policzWartosc(obiekt->pobierzPoziom()(),parametry.pobierzPoziom()(),parametry.pobierzIdentyfikatorPlanety()())));
				else
					poziom = obiekt->pobierzPoziom();
				return true;
		}			
		))
		{
			if(planeta.pobierzObiekt(identyfikator).pobierzPoziom()<poziom)
				return false;
		}
	}
	return true;
}

bool Wymagania::czySpelniaKoszty( const Ilosc& ilosc, const PodstawoweParametry& parametry ) const{
	if(koszty_.empty())
		return true;
	const Planeta& planeta = Aplikacja::getInstance().getGra().getUzytkownik().getPlaneta(parametry.pobierzIdentyfikatorPlanety());
	for( auto element : koszty_ ){
		Ilosc iloscObiektow;
		Identyfikator identyfikator;
		if(element.wykonaj(
			[&parametry,&iloscObiektow,&identyfikator](Cena::TypObiektu obiekt,Cena::Zmiana zmiana)->bool{
				if (!obiekt)
					return false;
				identyfikator = obiekt->pobierzIdentyfikator();
				if(zmiana)
					iloscObiektow = Ilosc(static_cast<Ilosc::type_name>(zmiana->policzWartosc(obiekt->getIlosc()(),parametry.pobierzPoziom()(),parametry.pobierzIdentyfikatorPlanety()())));
				else
					iloscObiektow = obiekt->getIlosc();
				return true;
		}			
		))
		{
			if( planeta.pobierzObiekt(identyfikator).pobierzIlosc() < (iloscObiektow*ilosc ) )
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
