#include "Statek.h"
#include "StatekInfo.h"
#include "Logger.h"
#include "DefinicjeWezlowXML.h"
#include "MenedzerTranzakcji.h"
#include "Zlecenia.h"

Statek::Statek( const Ilosc& ilosc, const Poziom& poziom, const Identyfikator& identyfikatorPlanety, const StatekInfo& statekInfo )
	: PodstawoweParametry(poziom, identyfikatorPlanety), Obiekt( ilosc, poziom, identyfikatorPlanety, statekInfo ), JednostkaAtakujaca(poziom,identyfikatorPlanety,statekInfo),
	JednostkaLatajaca(poziom,identyfikatorPlanety,statekInfo), Ladownia(poziom,identyfikatorPlanety,statekInfo), Hangar(poziom,identyfikatorPlanety,statekInfo), statekinfo_(statekInfo)
{
}

Statek::Statek( const Ilosc& ilosc, const PodstawoweParametry& podstawoweParametry, const StatekInfo& statekInfo )
	: PodstawoweParametry(podstawoweParametry), Obiekt( ilosc, podstawoweParametry, statekInfo ), JednostkaAtakujaca(podstawoweParametry,statekInfo),
	JednostkaLatajaca(podstawoweParametry,statekInfo), Ladownia(podstawoweParametry,statekInfo), Hangar(podstawoweParametry,statekInfo), statekinfo_(statekInfo)
{
}

ZuzyciePaliwa Statek::wyliczZuzyciePaliwa( const Dystans& dystans , const Predkosc& predkosc ) const {
	return ZuzyciePaliwa( ilosc_() * JednostkaLatajaca::wyliczZuzyciePaliwa(dystans,predkosc)()  );
}

Statek* Statek::kopia() const{
	return new Statek(*this);
}

Statek::~Statek(){
}

bool Statek::czyMoznaDodacDoHangaru() const{
	return statekinfo_.czyMoznaDodacDoHangaru();
}

Statek* Statek::podziel( const Ilosc& ilosc ){
	if( ilosc_>ilosc ){
		MenedzerTranzakcji tranzakcja;
		Statek* o = new Statek( ilosc , *this, this->statekinfo_ );
		Statek* statek = this;
		tranzakcja.dodaj( make_shared< Zlecenie< const Ilosc , Ilosc > >(ilosc , ilosc_, 
		[]( const Ilosc& ilosc , Ilosc& ilosc_s)->bool{ ilosc_s -= ilosc; return true; },
		[&statek]( const Ilosc& ilosc , Ilosc& ilosc_s)->bool{ ilosc_s += ilosc; statek->przeliczZajeteMiejsceLadowni(); statek->przeliczZajeteMiejsceHangaru(); return true; }) );

		tranzakcja.dodaj( make_shared< Zlecenie< Statek , Statek > >(*statek , *statek, 
		[](Statek& o , Statek& s)->bool{ o.przeliczZajeteMiejsceLadowni(); o.przeliczZajeteMiejsceHangaru(); return true; },
		[](Statek& o , Statek& s)->bool{ return true; }) );

		Hangar::Zbiornik zbHangar;
		Ladownia::Zbiornik zbLadownia;

		tranzakcja.dodaj( make_shared< Zlecenie< Statek , Statek > >(*o , *statek, 
		[&zbHangar](Statek& o , Statek& s)->bool{ 
			if(s.wolneMiejsceHangaru() < Fluktuacja(0.0)){
				zbHangar = s.podzielHangar( s.Hangar::zajete_ - s.pobierzPojemnoscMaksymalnaHangaru(), o.pobierzPojemnoscMaksymalnaHangaru());
				return !zbHangar.pusty();
			}
			return true;
		},
		[&zbHangar](Statek& o , Statek& s)->bool{ return s.Hangar::obiekty_.przeniesWszystkie(zbHangar); }) );

		tranzakcja.dodaj( make_shared< Zlecenie< Statek , Statek > >(*o , *statek, 
		[&zbHangar](Statek& o , Statek& s)->bool{ return o.Hangar::obiekty_.przeniesWszystkie(zbHangar);},
		[&zbHangar](Statek& o , Statek& s)->bool{ return true; }) );

		tranzakcja.dodaj( make_shared< Zlecenie< Statek , Statek > >(*o , *statek, 
		[&zbLadownia](Statek& o , Statek& s)->bool{ 
			if(s.wolneMiejsceLadowni() < Fluktuacja(0.0)){
				zbLadownia = s.podzielLadownie( s.Ladownia::zajete_ - s.pobierzPojemnoscMaksymalnaLadowni(), o.pobierzPojemnoscMaksymalnaLadowni());
				return !zbLadownia.pusty();
			}
			return true;
		},
		[&zbLadownia](Statek& o , Statek& s)->bool{ return s.Ladownia::obiekty_.przeniesWszystkie(zbLadownia); }) );

		tranzakcja.dodaj( make_shared< Zlecenie< Statek , Statek > >(*o , *statek, 
		[&zbLadownia](Statek& o , Statek& s)->bool{ return o.Ladownia::obiekty_.przeniesWszystkie(zbLadownia);},
		[&zbLadownia](Statek& o , Statek& s)->bool{ return true; }) );
		
		if(tranzakcja.wykonaj())
			return o;
	}
	return nullptr;
}	

bool Statek::polacz(const ObiektBazowy& obiektbazowy ){
	if(czyMoznaPolaczyc(obiektbazowy)){
		Statek & t = (Statek&)obiektbazowy;
		Statek* statek = this;
		MenedzerTranzakcji tranzakcja;

		tranzakcja.dodaj( make_shared< Zlecenie< const Ilosc , Ilosc > >(obiektbazowy.pobierzIlosc() , ilosc_, 
		[&statek,&t]( const Ilosc& ilosc , Ilosc& ilosc_s)->bool{ ilosc_s += ilosc; statek->przeliczZajeteMiejsceLadowni(); statek->przeliczZajeteMiejsceHangaru(); t.przeliczZajeteMiejsceLadowni(); t.przeliczZajeteMiejsceHangaru(); return true; },
		[&statek,&t]( const Ilosc& ilosc , Ilosc& ilosc_s)->bool{ ilosc_s -= ilosc; statek->przeliczZajeteMiejsceLadowni(); statek->przeliczZajeteMiejsceHangaru(); t.przeliczZajeteMiejsceLadowni(); t.przeliczZajeteMiejsceHangaru(); return true; }) );

		tranzakcja.dodaj( make_shared< Zlecenie< Statek , Statek > >(t , *statek, 
		[](Statek& o , Statek& s)->bool{ return s.pobierzPojemnoscMaksymalnaLadowni() >= (o.pobierzZajeteMiejsceLadowni()+s.pobierzZajeteMiejsceLadowni());},
		[](Statek& o , Statek& s)->bool{ return true; }) );

		tranzakcja.dodaj( make_shared< Zlecenie< Statek , Statek > >(t , *statek, 
		[](Statek& o , Statek& s)->bool{ return s.pobierzPojemnoscMaksymalnaHangaru() >= (o.pobierzZajeteMiejsceHangaru()+s.pobierzZajeteMiejsceHangaru());},
		[](Statek& o , Statek& s)->bool{ return true; }) );

		tranzakcja.dodaj( make_shared< Zlecenie< Statek , Statek > >(t , *statek, 
		[](Statek& o , Statek& s)->bool{ return s.polaczLadownie(o);},
		[](Statek& o , Statek& s)->bool{ return false; }) );

		tranzakcja.dodaj( make_shared< Zlecenie< Statek , Statek > >(t , *statek, 
		[](Statek& o , Statek& s)->bool{ return s.polaczHangar(o);},
		[](Statek& o , Statek& s)->bool{ return false; }) );
		
		tranzakcja.dodaj( make_shared< Zlecenie< Statek , Statek > >( *statek, *statek, 
		[]( Statek& o , Statek& s )->bool{ s.przeliczZajeteMiejsceLadowni(); s.przeliczZajeteMiejsceHangaru(); return true; },
		[]( Statek& o , Statek& s )->bool{ return true; }) );

		return tranzakcja.wykonaj();
	}
	return false;
}

Obrazenia Statek::pobierzAtak() const{
	return Obrazenia (JednostkaAtakujaca::pobierzAtak()() * ilosc_());
}

Obrazenia Statek::pobierzPancerz() const{
	return Obrazenia (JednostkaAtakujaca::pobierzPancerz()() * ilosc_());
}

Obrazenia Statek::pobierzOslone() const{
	return Obrazenia (JednostkaAtakujaca::pobierzOslone()() * ilosc_());
}

Objetosc Statek::pobierzPojemnoscMaksymalnaLadowni() const{
	return Ladownia::pobierzPojemnoscMaksymalnaLadowni()*pobierzIlosc();
}

Objetosc Statek::pobierzPojemnoscMaksymalnaHangaru() const{
	return Hangar::pobierzPojemnoscMaksymalnaHangaru()*pobierzIlosc();
}

Masa Statek::pobierzMasaSilnika()const{
	return Masa(JednostkaLatajaca::pobierzMasaSilnika()()* ilosc_());
}

ZuzyciePaliwa Statek::pobierzJednostkoweZuzyciePaliwa()const{
	return ZuzyciePaliwa(JednostkaLatajaca::pobierzJednostkoweZuzyciePaliwa()()*ilosc_() );
}

Masa Statek::pobierzMase() const{
	return Obiekt::pobierzMase() + Ladownia::pobierzMaseZawartosciLadowni() + Statek::pobierzMasaSilnika();
}

const StatekInfo& Statek::pobierzStatekInfo() const{
	return statekinfo_;
}

bool Statek::zapisz( tinyxml2::XMLElement* wezel ) const {
	tinyxml2::XMLElement* element = wezel->GetDocument()->NewElement(WEZEL_XML_STATEK);
	wezel->LinkEndChild( element );
	return Obiekt::zapisz(element) && Ladownia::zapisz(element) && Hangar::zapisz(element);
}

bool Statek::odczytaj( tinyxml2::XMLElement* wezel ) {
	return Obiekt::odczytaj(wezel) && Ladownia::odczytaj(wezel->FirstChildElement(WEZEL_XML_LADOWNIA)) && Hangar::odczytaj(wezel->FirstChildElement(WEZEL_XML_HANGAR));
}

Masa Statek::calkowitaMasaJednostki() const{
	return Statek::pobierzMase();
}

string Statek::napis() const{
	Logger str(NAZWAKLASY(Statek));
	str.dodajKlase(Obiekt::napis());
	str.dodajKlase(JednostkaAtakujaca::napis());
	str.dodajKlase(JednostkaLatajaca::napis());
	str.dodajKlase(Ladownia::napis());
	str.dodajKlase(Hangar::napis());
	str.dodajPole(NAZWAKLASY(StatekInfo)+"ID",statekinfo_.pobierzIdentyfikator());
	return str.napis();
}
