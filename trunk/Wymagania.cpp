#include "Wymagania.h"
#include "Logger.h"
#include "Aplikacja.h"
#include "XmlBO.h"
#include "definicjeWezlowXML.h"
#include "LiczenieKosztow.h"

Wymagania::Wymagania( TiXmlElement* n  ) throw(WyjatekParseraXML)
{
	if(n){
		try{
			auto e = n->FirstChildElement(WEZEL_XML_WYMOG);
			while(e){
				dodajWymog(Wymog(e,WEZEL_XML_OBIEKTBASE_INFO));
				e = e->NextSiblingElement(WEZEL_XML_WYMOG);
			}

			auto c = XmlBO::ZnajdzWezelJezeli<NOTHROW>(n->FirstChildElement(WEZEL_XML_CZAS),WEZEL_XML_ZMIANA,ATRYBUT_XML_FOR,WEZEL_XML_CZAS);
			if(c)
				zmCzasuBudowy=Aplikacja::getInstance().getGra().getZmianaFabryka().Tworz(c);
			e = n->FirstChildElement(WEZEL_XML_CENA);
			while(e){
				dodajCene(Cena(e,WEZEL_XML_SUROWCE));
				e = e->NextSiblingElement(WEZEL_XML_CENA);
			}

		}catch(exception& e){
			throw WyjatekParseraXML(EXCEPTION_PLACE,e,WyjatekParseraXML::trescBladStrukturyXml);
		}
		
	}
}


Czas Wymagania::pobierzCzasBudowy( const Ilosc& i, const PodstawoweParametry& p )const{
	auto k = PobierzKoszty(i,p);
	Czas suma;
	for( auto i : k ){
		if(i)
			suma+=i->pobierzCzas();
	}
	if(zmCzasuBudowy){		
		suma = zmCzasuBudowy->policzWartosc(suma(),static_cast<int>(p.pobierzPoziom()()),p.pobierzIdentyfikatorPlanety()());
	}
	return suma;
}

bool Wymagania::czySpelniaWymagania( const Ilosc& i, const PodstawoweParametry& p ) const{
	return czySpelniaKoszty(i,p) && czySpelniaWymogi(p);
}

bool Wymagania::dodajWymog( Wymog& o ){
	bool zamien = true;
	for(auto iter = warunki.begin() ; iter != warunki.end() ; ++iter ){
		if(iter->wykonaj(
			[&o,&zamien](Wymog::TypObiektu obiekt,Wymog::Zmiana zmiana)->bool{
				if(!obiekt)
					return false;
				auto id = obiekt->pobierzIdentyfikator();
				auto poziom = obiekt->pobierzPoziom();
				return o.wykonaj(
					[&id,&poziom,&zamien](Wymog::TypObiektu obiekt,Wymog::Zmiana zmiana)->bool{
							if(!obiekt)
								return false;
							if( id == obiekt->pobierzIdentyfikator() ){
								zamien = ( poziom < obiekt->pobierzPoziom() );
								return true;
							}
							return false;
						}
					);
				}
		)){
			if(zamien){
				warunki.erase(iter);
				warunki.push_back(o);
			}
			return zamien;
		}
	}
	warunki.push_back(o);
	return true;
}

bool Wymagania::dodajCene( Cena& o ){
	bool zamien = true;
	for(auto iter = koszty.begin() ; iter != koszty.end() ; ++iter ){
		if(iter->wykonaj(
			[&o,&zamien](Cena::TypObiektu obiekt,Cena::Zmiana zmiana)->bool{
				if(!obiekt)
					return false;
				auto id = obiekt->pobierzIdentyfikator();
				auto ilosc = obiekt->getIlosc();
				return o.wykonaj(
					[&id,&ilosc,&zamien](Cena::TypObiektu obiekt,Cena::Zmiana zmiana)->bool{
							if(!obiekt)
								return false;
							if( id == obiekt->pobierzIdentyfikator() ){
								zamien = ( ilosc < obiekt->getIlosc() );
								return true;
							}
							return false;
						}
					);
				}
		)){
			if(zamien){
				koszty.erase(iter);
				koszty.push_back(o);
			}
			return zamien;
		}
	}
	koszty.push_back(o);
	return true;
}

bool Wymagania::czySpelniaWymogi( const PodstawoweParametry& p ) const{	
	if(warunki.empty())
		return true;
	const Planeta& planeta = Aplikacja::getInstance().getGra().getUzytkownik().getPlaneta(p.pobierzIdentyfikatorPlanety());
	for (auto a : warunki){
		Poziom poz;
		Identyfikator id;
		if(a.wykonaj(
			[&p,&poz,&id](Wymog::TypObiektu obiekt,Wymog::Zmiana zmiana)->bool{
					if (!obiekt)
						return false;
					id = obiekt->pobierzIdentyfikator();
					if(zmiana)
						poz = Poziom(static_cast<Poziom::type_name>(zmiana->policzWartosc(obiekt->pobierzPoziom()(),p.pobierzPoziom()(),p.pobierzIdentyfikatorPlanety()())));
					else
						poz = obiekt->pobierzPoziom();
					return true;
				}			
			))
		{
			if(planeta.pobierzObiekt(id).pobierzPoziom()<poz)
				return false;
		}
	}
	return true;
}

bool Wymagania::czySpelniaKoszty( const Ilosc& i, const PodstawoweParametry& p ) const{
	const Planeta& planeta = Aplikacja::getInstance().getGra().getUzytkownik().getPlaneta(p.pobierzIdentyfikatorPlanety());
	for( auto e : koszty ){
		Ilosc ilosc;
		Identyfikator id;
		if(e.wykonaj(
			[&p,&ilosc,&id](Cena::TypObiektu obiekt,Cena::Zmiana zmiana)->bool{
					if (!obiekt)
						return false;
					id = obiekt->pobierzIdentyfikator();
					if(zmiana)
						ilosc = Ilosc(static_cast<Ilosc::type_name>(zmiana->policzWartosc(obiekt->getIlosc()(),p.pobierzPoziom()(),p.pobierzIdentyfikatorPlanety()())));
					else
						ilosc = obiekt->getIlosc();
					return true;
				}			
			))
		{
			if(planeta.pobierzObiekt(id).pobierzIlosc()<ilosc)
				return false;
		}
	}
	return true;
}


Wymagania::PrzetworzoneWymogi Wymagania::listaWarunkow( const PodstawoweParametry& p ) const{
	PrzetworzoneWymogi tmp;
	for (auto a : warunki){
		Wymog::TypObiektu rezultat = nullptr;
		a.wykonaj(
			[&rezultat,&p](Wymog::TypObiektu obiekt,Wymog::Zmiana zmiana)->bool{
					if(!obiekt)
						return false;
					if(zmiana)
						rezultat = Wymog::TypObiektu ( new TypWymogu( *(obiekt), Poziom( static_cast<Poziom::type_name>(floorl(zmiana->policzWartosc( obiekt->pobierzPoziom()() , static_cast<int>(p.pobierzPoziom()()),p.pobierzIdentyfikatorPlanety()() ))) ) ) );
					else
						rezultat = Wymog::TypObiektu ( new TypWymogu( *(obiekt), Poziom( obiekt->pobierzPoziom() ) ) );
					return true;
				}
			);
		if(rezultat)
			tmp.push_back(rezultat);
	}
	return tmp;
}

Wymagania::PrzetworzonaCena Wymagania::PobierzKoszty(const Ilosc& ilosc, const PodstawoweParametry& p) const{
	PrzetworzonaCena zb;
	for( auto e : koszty ){
		LiczenieKosztow (e,zb,ilosc,p)();
	}
	return zb;
}
string Wymagania::napis() const{
	Logger str(NAZWAKLASY(Wymagania));
	return str.napis();
}