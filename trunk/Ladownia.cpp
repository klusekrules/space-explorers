#include "Ladownia.h"
#include "LadowniaInfo.h"
#include "Statek.h"
#include "Surowce.h"
#include "Aplikacja.h"
#include "Utils.h"
#include "DefinicjeWezlowXML.h"
#include <algorithm>
#include <functional>

	
Ladownia::Ladownia( const Poziom& p, const Identyfikator& idP, const LadowniaInfo& l )
	: PodstawoweParametry(p, idP), obiekty(), zajete(), ladowniaInfo(l)
{
}

Ladownia::Ladownia( const PodstawoweParametry& p, const LadowniaInfo& l )
	: PodstawoweParametry(p), obiekty(), zajete(), ladowniaInfo(l)
{
}

Fluktuacja Ladownia::WolneMiejsce() const{
	return Fluktuacja( 1.0 ) - ( zajete / getPojemnoscMax() );
}

Ilosc Ladownia::SprawdzIloscObiektow( const Klucz& itID ) const{
	return obiekty.pobierz(itID)->pobierzIlosc();
}

bool Ladownia::Polacz( Ladownia& l ){
	return obiekty.przeniesWszystkie(l.obiekty);
}

bool Ladownia::czMoznaDodacDoLadownii( const Statek& c ) const {
	return true;
}

bool Ladownia::czMoznaDodacDoLadownii( const Surowce& c ) const {
	return c.czyTypPrzyrostowy();
}

//Tranzakcyjna
bool Ladownia::DodajObiektDoLadowni( Item& obiekt ){
	if(!obiekt.czMoznaDodacDoLadownii(*this)){
		return false;
	}
	if( obiekt.pobierzObjetosc()/obiekt.pobierzIlosc() > ladowniaInfo.getPojemnoscMaksymalna(*this) || (obiekt.pobierzObjetosc() + zajete) > getPojemnoscMax() ){
		return false;
	}
	shared_ptr<Obiekt> kopia = shared_ptr<Obiekt>(obiekt.kopia());
	kopia->ustawIdentyfikatorPlanety(Identyfikator());
	bool rezultat = obiekty.dodaj(kopia);
	przeliczZajeteMiejsce();
	return rezultat;		
}	

Ladownia::Zbiornik Ladownia::OproznijLadownie(){
	Zbiornik tmp;
	tmp.przeniesWszystkie(obiekty);
	przeliczZajeteMiejsce();
	return tmp;
}

Ladownia::Item& Ladownia::PobierzObiekt( const Klucz& itID, const Ilosc& isIlosc ) throw( NieznalezionoObiektu, NiepoprawnaIloscObiektow ){
	if(obiekty.pusty())
		throw NieznalezionoObiektu(EXCEPTION_PLACE,itID.napis());

	try{
		Obiekt& o = *obiekty.pobierz(itID);
		if( isIlosc == o.pobierzIlosc() ){
			obiekty.wyjmij(itID);
			przeliczZajeteMiejsce();
			return o;
		}

		if( isIlosc < o.pobierzIlosc() ){
			Obiekt *k = o.podziel(isIlosc);
			przeliczZajeteMiejsce();
			return *k;
		}

		if( isIlosc == Ilosc() ){
			throw NieznalezionoObiektu(EXCEPTION_PLACE,o.napis());
		}

		if( isIlosc > o.pobierzIlosc() ){
			throw NiepoprawnaIloscObiektow(EXCEPTION_PLACE,isIlosc);
		}
	}catch( OgolnyWyjatek& ){
		throw;
	}	
	throw NiepoprawnaIloscObiektow(EXCEPTION_PLACE,isIlosc);
}

/* Zwr�cony zbiornik ma obj�to�� z przedzia�u  < min , max >  */
//Tranzakcyjna
Ladownia::Zbiornik* Ladownia::PodzielLadownie( const Objetosc& oMin , const Objetosc& oMax  ){
	Zbiornik *zb = new Zbiornik();
	
	Objetosc tObj ( 0.0 );
	Objetosc tMin ( oMin );

	//Je�eli objeto�� czekiwana jest r�wna 0 to zwracamy pusty zbior obiekt�w
	if( oMax == tObj )
		return zb;

	// Je�eli obj�to�� minimalna jest ujemna to j� zerujemy
	if( tMin < tObj )
		tMin = tObj;

	//Je�eli obj�to�� oczekiwana mniejsza od 0 lub obj�to�� minimalna wi�ksza od pojemno�ci 
	//lub obj�to�� minimalna wi�ksza od obj�to�ci docelowej.
	if( oMax < tObj || oMin > zajete || oMin > oMax ){
		delete zb;
		return nullptr;
	}
	//Sortujemy zbiornik, tak aby w pierwszej kolejno�ci by�y przegl�dane elementy o wi�kszym jednostkowym rozmiarze.
	Zbiornik kopia(obiekty);
	map<Objetosc,Klucz,greater<Objetosc> > posortowane;
	for( auto o : obiekty )
		posortowane.insert(make_pair(o.second->pobierzObjetosc()/o.second->pobierzIlosc(),o.first));

	/*
		Przechodzimy po elementach zbiornika i przepisujemy tyle ile si� da. Dopuszczamy dzielenie grup obiekt�w je�li mo�liwe.
	*/
	for( auto o : posortowane ){
		Objetosc objElementu(obiekty.pobierz(o.second)->pobierzObjetosc());
		if( objElementu + tObj <= oMax ){
			if(Zbiornik::przenies(o.second, kopia , *zb)){
				tObj += objElementu;
			}
		}else{
			Objetosc objPojedyncza( o.first );
			if( oMax - tObj >= objPojedyncza ){
				Ilosc liczbaElementow( floorl(( oMax() - tObj() ) / objPojedyncza()) );
				if( liczbaElementow >= Ilosc(1.0) ){
					if(Zbiornik::przenies(o.second,liczbaElementow, kopia , *zb)){
						tObj += Objetosc( objPojedyncza() * liczbaElementow() );
					}
				}
			}
		}
		if(tObj >= tMin)
			break;
	}
	if(tObj >= tMin){
		obiekty = kopia;
		przeliczZajeteMiejsce();
	}else{
		delete zb;
		return nullptr;
	}
	return zb;
}

void Ladownia::przeliczZajeteMiejsce(){
	zajete=Objetosc(0);
	for( auto o : obiekty){
		zajete += o.second->pobierzObjetosc();
	}
}

Masa Ladownia::getMasaZawartosciLadowni()const {
	Masa m (0);
	for( auto o : obiekty){
		m += o.second->pobierzMase();
	}
	return m;
}

Ladownia::ListaKluczy Ladownia::PobierzListeIdObiektow() const{
	return obiekty.listaKluczy();
}

const Ladownia::Zbiornik& Ladownia::getPrzewozoneObiekty() const{
	return obiekty;
}

const Objetosc& Ladownia::getZajeteMiejsce() const{
	return zajete;
}

Objetosc Ladownia::getPojemnoscMax() const{
	return ladowniaInfo.getPojemnoscMaksymalna(*this);
}

bool Ladownia::zapisz( TiXmlElement* e ) const {
	TiXmlElement* n = new TiXmlElement(WEZEL_XML_LADOWNIA);
	e->LinkEndChild( n );
	n->SetAttribute(ATRYBUT_XML_ZAJETE_MIEJSCE,zajete.napis());
	for( auto o : obiekty){
		if(!o.second->zapisz(n))
			return false;
	}
	return true;
}

bool Ladownia::odczytaj (TiXmlElement* e) {
	if(e){
		auto c = e->Attribute(ATRYBUT_XML_ZAJETE_MIEJSCE);
		if(!c)
			return false;
		zajete(stod(c));
		try{
			for(TiXmlElement* n = e->FirstChildElement(); n != nullptr ; n = n->NextSiblingElement()){
				string c = n->Attribute(ATRYBUT_XML_IDENTYFIKATOR);
				if(c.empty())
					return false;
				Utils::trim(c);
				Identyfikator id(stoi(c,nullptr,0));
				shared_ptr<Obiekt> p = shared_ptr<Obiekt>(Aplikacja::getInstance().getGra().getObiekt(id).tworzEgzemplarz(Ilosc(),Identyfikator()));			
				if(!p->odczytaj(n) ){
					return false;
				}
				obiekty.dodaj(p);
			}
		}catch(...){
			return false;
		}
		return true;
	}
	return false;
}

string Ladownia::napis() const{
	Logger str(NAZWAKLASY(Ladownia));
	str.dodajPole("Zajete Miejsce",zajete);
	str.dodajPole(NAZWAKLASY(Zbiornik),obiekty);
	str.dodajPole(NAZWAKLASY(LadowniaInfo)+"ID",ladowniaInfo.pobierzIdentyfikator());
	return str.napis();
}