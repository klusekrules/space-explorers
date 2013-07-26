#include "Ladownia.h"
#include "LadowniaInfo.h"
#include "Statek.h"
#include "Surowce.h"
#include "Aplikacja.h"
#include "Utils.h"
#include "DefinicjeWezlowXML.h"
#include <algorithm>
#include <functional>
#include "XmlBO.h"
	
Ladownia::Ladownia( const Poziom& poziom, const Identyfikator& identyfikatorPlanety, const LadowniaInfo& ladowniaInfo )
	: PodstawoweParametry(poziom, identyfikatorPlanety), obiekty_(), zajete_(), ladowniaInfo_(ladowniaInfo)
{
}

Ladownia::Ladownia( const PodstawoweParametry& podstawoweParametry, const LadowniaInfo& ladowniaInfo )
	: PodstawoweParametry(podstawoweParametry), obiekty_(), zajete_(), ladowniaInfo_(ladowniaInfo)
{
}

Ladownia::~Ladownia(){
}

Fluktuacja Ladownia::wolneMiejsce() const{
	return Fluktuacja( 1.0 ) - ( zajete_ / pobierzPojemnoscMaksymalna() );
}

Ilosc Ladownia::pobierzIloscObiektow( const Klucz& klucz ) const{
	auto element = obiekty_.pobierz(klucz);
	if(element)
		return element->pobierzIlosc();
	else
		return Ilosc(0);
}

bool Ladownia::polacz( Ladownia& ladownia ){
	return obiekty_.przeniesWszystkie(ladownia.obiekty_);
}

bool Ladownia::polacz( Zbiornik zbiornik ){
	return obiekty_.przeniesWszystkie(zbiornik);
}

bool Ladownia::czyMoznaDodacDoLadownii( const Statek& statek ) const {
	return true;
}

bool Ladownia::czyMoznaDodacDoLadownii( const Surowce& surowce ) const {
	return surowce.czyTypPrzyrostowy();
}

//Tranzakcyjna
bool Ladownia::dodajObiektDoLadowni( const Item& obiekt ){
	if(!obiekt.czyMoznaDodacDoLadownii(*this)){
		return false;
	}
	if( obiekt.pobierzObjetosc()/obiekt.pobierzIlosc() > ladowniaInfo_.pobierzPojemnoscMaksymalna(*this) || (obiekt.pobierzObjetosc() + zajete_) > pobierzPojemnoscMaksymalna() ){
		return false;
	}
	shared_ptr<Obiekt> kopia = shared_ptr<Obiekt>(obiekt.kopia());
	kopia->ustawIdentyfikatorPlanety(Identyfikator());
	bool rezultat = obiekty_.dodaj(kopia);
	przeliczZajeteMiejsce();
	return rezultat;		
}

//Tranzakcyjna
bool Ladownia::dodajObiektDoLadowni( shared_ptr<Item> obiekt ){
	if( !obiekt || !obiekt->czyMoznaDodacDoLadownii(*this)){
		return false;
	}
	if( obiekt->pobierzObjetosc()/obiekt->pobierzIlosc() > ladowniaInfo_.pobierzPojemnoscMaksymalna(*this) || (obiekt->pobierzObjetosc() + zajete_) > pobierzPojemnoscMaksymalna() ){
		return false;
	}
	auto identyfikator = obiekt->pobierzIdentyfikatorPlanety();
	obiekt->ustawIdentyfikatorPlanety(Identyfikator());
	bool rezultat = obiekty_.dodaj(obiekt);
	if(!rezultat)
		obiekt->ustawIdentyfikatorPlanety(identyfikator);
	else
		przeliczZajeteMiejsce();
	return rezultat;		
}

//Tranzakcyjna
Ladownia::Zbiornik Ladownia::oproznijLadownie(){
	Zbiornik tmp;
	tmp.przeniesWszystkie(obiekty_);
	przeliczZajeteMiejsce();
	return tmp;
}

shared_ptr<Ladownia::Item> Ladownia::wyjmijObiekt( const Klucz& klucz, const Ilosc& ilosc ){
	if(obiekty_.pusty() || ilosc == Ilosc())
		return nullptr;
	
	shared_ptr<Ladownia::Item> obiekt = obiekty_.pobierz(klucz);
		
	if( !obiekt || ilosc > obiekt->pobierzIlosc() )
		return nullptr;

	if( ilosc == obiekt->pobierzIlosc() ){
		obiekt = obiekty_.wyjmij(klucz);
		przeliczZajeteMiejsce();
		return obiekt;
	}

	shared_ptr<Ladownia::Item> czesc = shared_ptr<Ladownia::Item>(obiekt->podziel(ilosc));
	przeliczZajeteMiejsce();
	return czesc;
}

/* Zwrócony zbiornik ma objêtoœæ z przedzia³u  < min , max >  */
//Tranzakcyjna
Ladownia::Zbiornik Ladownia::podzielLadownie( const Objetosc& minimum , const Objetosc& maksimum  ){
	Zbiornik zbiornik;
	
	Objetosc tymczasowaObjetosc ( 0.0 );
	Objetosc tymczasoweMinimum ( minimum );

	//Je¿eli objetoœæ czekiwana jest równa 0 to zwracamy pusty zbior obiektów
	if( maksimum == tymczasowaObjetosc )
		return Zbiornik();

	// Je¿eli objêtoœæ minimalna jest ujemna to j¹ zerujemy
	if( tymczasoweMinimum < tymczasowaObjetosc )
		tymczasoweMinimum = tymczasowaObjetosc;

	//Je¿eli objêtoœæ oczekiwana mniejsza od 0 lub objêtoœæ minimalna wiêksza od pojemnoœci 
	//lub objêtoœæ minimalna wiêksza od objêtoœci docelowej.
	if( maksimum < tymczasowaObjetosc || minimum > zajete_ || minimum > maksimum ){
		return Zbiornik();
	}
	//Sortujemy zbiornik, tak aby w pierwszej kolejnoœci by³y przegl¹dane elementy o wiêkszym jednostkowym rozmiarze.
	Zbiornik kopia(obiekty_);
	map<Objetosc,Klucz,greater<Objetosc> > posortowane;
	for( auto element : obiekty_ )
		posortowane.insert(make_pair(element.second->pobierzObjetoscJednostkowa(),element.first));

	/*
		Przechodzimy po elementach zbiornika i przepisujemy tyle ile siê da. Dopuszczamy dzielenie grup obiektów jeœli mo¿liwe.
	*/
	for( auto element : posortowane ){
		Objetosc objElementu(obiekty_.pobierz(element.second)->pobierzObjetosc());
		if( objElementu + tymczasowaObjetosc <= maksimum ){
			if(Zbiornik::przenies(element.second, kopia , zbiornik)){
				tymczasowaObjetosc += objElementu;
			}
		}else{
			Objetosc objPojedyncza( element.first );
			if( maksimum - tymczasowaObjetosc >= objPojedyncza ){
				Ilosc liczbaElementow( floorl(( maksimum() - tymczasowaObjetosc() ) / objPojedyncza()) );
				if( liczbaElementow >= Ilosc(1.0) ){
					if(Zbiornik::przenies(element.second,liczbaElementow, kopia , zbiornik)){
						tymczasowaObjetosc += Objetosc( objPojedyncza() * liczbaElementow() );
					}
				}
			}
		}
		if(tymczasowaObjetosc >= tymczasoweMinimum)
			break;
	}
	if(tymczasowaObjetosc >= tymczasoweMinimum){
		obiekty_ = kopia;
		przeliczZajeteMiejsce();
	}else{
		return Zbiornik();
	}
	return zbiornik;
}

void Ladownia::przeliczZajeteMiejsce(){
	zajete_=Objetosc(0);
	for( auto element : obiekty_){
		zajete_ += element.second->pobierzObjetosc();
	}
}

Masa Ladownia::pobierzMaseZawartosciLadowni()const {
	Masa masa (0);
	for( auto element : obiekty_){
		masa += element.second->pobierzMase();
	}
	return masa;
}

Ladownia::ListaKluczy Ladownia::pobierzListeIdentyfikatorowObiektow() const{
	return obiekty_.listaKluczy();
}

const Ladownia::Zbiornik& Ladownia::pobierzPrzewozoneObiekty() const{
	return obiekty_;
}

const Objetosc& Ladownia::pobierzZajeteMiejsce() const{
	return zajete_;
}

Objetosc Ladownia::pobierzDostepneMiejsce() const{
	return pobierzPojemnoscMaksymalna() - zajete_;
}

Objetosc Ladownia::pobierzPojemnoscMaksymalna() const{
	return ladowniaInfo_.pobierzPojemnoscMaksymalna(*this);
}

Objetosc Ladownia::pobierzPojemnoscJednostkowa() const{
	return ladowniaInfo_.pobierzPojemnoscMaksymalna(*this);
}

bool Ladownia::zapisz( TiXmlElement* wezel ) const {
	TiXmlElement* element = new TiXmlElement(WEZEL_XML_LADOWNIA);
	wezel->LinkEndChild( element );
	element->SetAttribute(ATRYBUT_XML_ZAJETE_MIEJSCE,zajete_.napis());
	for( auto o : obiekty_){
		if(!o.second->zapisz(element))
			return false;
	}
	return true;
}

bool Ladownia::odczytaj (TiXmlElement* wezel ) {
	if(wezel){
		if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_ZAJETE_MIEJSCE,zajete_))
			return false;
		try{
			Gra& gra = Aplikacja::pobierzInstancje().pobierzGre();
			TiXmlElement* element = wezel->FirstChildElement(); 
			while(element){
				Identyfikator identyfikator;
				if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_IDENTYFIKATOR,identyfikator))
					return false;
				shared_ptr<Obiekt> obiekt = shared_ptr<Obiekt>(gra.pobierzObiekt(identyfikator).tworzEgzemplarz(Ilosc(),Identyfikator()));			
				if(!obiekt->odczytaj(element) ){
					return false;
				}
				obiekty_.dodaj(obiekt);
				element = element->NextSiblingElement();
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
	str.dodajPole("Zajete Miejsce",zajete_);
	str.dodajPole(NAZWAKLASY(Zbiornik),obiekty_);
	str.dodajPole(NAZWAKLASY(LadowniaInfo)+"ID",ladowniaInfo_.pobierzIdentyfikator());
	return str.napis();
}
