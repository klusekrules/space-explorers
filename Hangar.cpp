#include "Hangar.h"
#include "XmlBO.h"
#include "Logger\Logger.h"
#include "definicjeWezlowXML.h"
#include "Aplikacja.h"
#include "HangarInfo.h"
#include "Statek.h"
#include "MenedzerTranzakcji.h"
#include "Zlecenia.h"

Hangar::Hangar( const Poziom& poziom, const Identyfikator& identyfikatorPlanety, const HangarInfo& hangarInfo )
	: PodstawoweParametry(poziom,identyfikatorPlanety), hangarInfo_(hangarInfo)
{
}

Hangar::Hangar( const PodstawoweParametry& podstawoweParametry, const HangarInfo& hangarInfo )
	: PodstawoweParametry(podstawoweParametry), hangarInfo_(hangarInfo)
{
}

Hangar::~Hangar(void)
{
}

Fluktuacja Hangar::wolneMiejsceHangaru() const{
	return Fluktuacja( 1.0 ) - ( zajete_ / pobierzPojemnoscMaksymalnaHangaru() );
}

bool Hangar::dodajStatekDoHangaru( const Item& obiekt ){
	if( !obiekt.czyMoznaDodacDoHangaru()
		|| obiekt.pobierzObjetosc()/obiekt.pobierzIlosc() > hangarInfo_.pobierzMaksymalnaIloscPrzewozonychStatkow(*this) 
		|| (obiekt.pobierzObjetosc() + zajete_) > pobierzPojemnoscMaksymalnaHangaru() ){
		return false;
	}
	shared_ptr<Item> kopia = shared_ptr<Item>(obiekt.kopia());
	kopia->ustawIdentyfikatorPlanety(Identyfikator());
	bool rezultat = obiekty_.dodaj(kopia);
	przeliczZajeteMiejsceHangaru();
	return rezultat;
}

bool Hangar::dodajStatekDoHangaru( shared_ptr<Item> obiekt ){
	if( !obiekt 
		|| !obiekt->czyMoznaDodacDoHangaru() 
		|| obiekt->pobierzObjetosc()/obiekt->pobierzIlosc() > hangarInfo_.pobierzMaksymalnaIloscPrzewozonychStatkow(*this) 
		|| (obiekt->pobierzObjetosc() + zajete_) > pobierzPojemnoscMaksymalnaHangaru() ){
		return false;
	}
	MenedzerTranzakcji tranzakcja;
	Identyfikator nowe;
	Hangar* hangar = this;

	tranzakcja.dodaj( make_shared<ZlecenieUstawIdentyfikatorPlanety>(nowe , static_cast< shared_ptr<PodstawoweParametry> >(obiekt)) );

	tranzakcja.dodaj( make_shared< Zlecenie< Hangar::Zbiornik , shared_ptr< Item > > >(obiekty_ , obiekt, 
		[](Hangar::Zbiornik& h , shared_ptr< Item >& s)->bool{ return h.dodaj(s); },
		[](Hangar::Zbiornik& h , shared_ptr< Item >& s)->bool{ return false; }) );

	tranzakcja.dodaj( make_shared< Zlecenie< Hangar , Hangar > >( *hangar , *hangar, 
		[](Hangar& h , Hangar& s)->bool{ h.przeliczZajeteMiejsceHangaru(); return true; },
		[](Hangar& h , Hangar& s)->bool{ return false; }) );

	return tranzakcja.wykonaj();
}

Objetosc Hangar::pobierzPojemnoscMaksymalnaHangaru() const{
	return hangarInfo_.pobierzMaksymalnaIloscPrzewozonychStatkow(*this);
}

Objetosc Hangar::pobierzPojemnoscJednostkowaHangaru() const{
	return hangarInfo_.pobierzMaksymalnaIloscPrzewozonychStatkow(*this);
}

bool Hangar::polaczHangar( Hangar& hangar ){
	return obiekty_.przeniesWszystkie(hangar.obiekty_);
}

bool Hangar::polaczHangar( Zbiornik zbiornik ){
	return obiekty_.przeniesWszystkie(zbiornik);
}

Hangar::Zbiornik Hangar::oproznijHangar(){
	Zbiornik tmp;
	tmp.przeniesWszystkie(obiekty_);
	przeliczZajeteMiejsceHangaru();
	return tmp;
}

Ilosc Hangar::pobierzIloscStatkow( const Klucz& klucz ) const{
	auto element = obiekty_.pobierz(klucz);
	if(element)
		return element->pobierzIlosc();
	else
		return Ilosc(0);
}

shared_ptr<Hangar::Item> Hangar::wyjmijStatek( const Klucz& klucz , const Ilosc& ilosc ){
	if(obiekty_.pusty() || ilosc == Ilosc())
		return nullptr;
	
	shared_ptr<Item> obiekt = obiekty_.pobierz(klucz);
		
	if( !obiekt || ilosc > obiekt->pobierzIlosc() )
		return nullptr;

	if( ilosc == obiekt->pobierzIlosc() ){
		obiekt = obiekty_.wyjmij(klucz);
		przeliczZajeteMiejsceHangaru();
		return obiekt;
	}

	shared_ptr<Item> czesc = shared_ptr<Item>(obiekt->podziel(ilosc));
	przeliczZajeteMiejsceHangaru();
	return czesc;
}

Hangar::ListaKluczy Hangar::pobierzListeIdentyfikatorowStatkow() const{
	return obiekty_.listaKluczy();
}

const Hangar::Zbiornik& Hangar::pobierzPrzewozoneStatki() const{
	return obiekty_;
}

Hangar::Zbiornik Hangar::podzielHangar( const Objetosc& minimum , const Objetosc& maksimum ){
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
	vector< pair<Objetosc,Klucz> > posortowane;
	for( auto element : obiekty_ )
		posortowane.push_back(make_pair(element.second->pobierzObjetoscJednostkowa(),element.first));
	sort(posortowane.begin(),posortowane.end(), greater< pair<Objetosc,Klucz> >());

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
		przeliczZajeteMiejsceHangaru();
	}else{
		return Zbiornik();
	}
	return zbiornik;
}

const Objetosc& Hangar::pobierzZajeteMiejsceHangaru() const{
	return zajete_;
}

Objetosc Hangar::pobierzDostepneMiejsceHangaru() const{
	return pobierzPojemnoscMaksymalnaHangaru() - zajete_;
}

void Hangar::przeliczZajeteMiejsceHangaru(){
	zajete_=Objetosc(0);
	for( auto element : obiekty_){
		zajete_ += element.second->pobierzObjetosc();
	}
}

bool Hangar::zapisz( tinyxml2::XMLElement* wezel ) const {
	tinyxml2::XMLElement* element = wezel->GetDocument()->NewElement(WEZEL_XML_HANGAR);
	wezel->LinkEndChild( element );
	if(zajete_ < Objetosc(0) )
			return false;
	element->SetAttribute(ATRYBUT_XML_ZAJETE_MIEJSCE,zajete_.napis().c_str());
	for( auto o : obiekty_){
		if(!o.second->zapisz(element))
			return false;
	}
	return true;
}

bool Hangar::odczytaj (tinyxml2::XMLElement* wezel ) {
	if(wezel){
		if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_ZAJETE_MIEJSCE,zajete_))
			return false;
		if(zajete_ < Objetosc(0) )
			return false;
		try{
			Gra& gra = Aplikacja::pobierzInstancje().pobierzGre();
			tinyxml2::XMLElement* element = XmlBO::ZnajdzWezel<NOTHROW>(wezel,WEZEL_XML_STATEK);
			while(element){
				shared_ptr<Statek> obiekt = gra.tworzStatek(element);			
				if( !obiekt || !obiekt->odczytaj(element) ){
					Utils::generujWyjatekBleduStruktury(EXCEPTION_PLACE,element);
				}
				obiekty_.dodaj(obiekt);
				element = XmlBO::ZnajdzWezel<NOTHROW>(wezel,WEZEL_XML_STATEK,element);
			}
		}catch(...){
			return false;
		}
		return true;
	}
	return false;
}

string Hangar::napis() const{
	Logger str(NAZWAKLASY(Hangar));
	str.dodajPole("Zajete Miejsce",zajete_);
	str.dodajPole(NAZWAKLASY(Zbiornik),obiekty_);
	str.dodajPole(NAZWAKLASY(HangarInfo)+"ID",hangarInfo_.pobierzIdentyfikator());
	return str.napis();
}
