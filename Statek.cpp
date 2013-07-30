#include "Statek.h"
#include "StatekInfo.h"
#include "Logger.h"
#include "DefinicjeWezlowXML.h"

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
		Statek* o = new Statek( ilosc , *this, this->statekinfo_ );
		ilosc_-=ilosc;
		this->przeliczZajeteMiejsceLadowni();
		this->przeliczZajeteMiejsceHangaru();
		Hangar::Zbiornik zbHangar;
		Ladownia::Zbiornik zbLadownia;
		if(this->wolneMiejsceHangaru() < Fluktuacja(0.0)){
			zbHangar = this->podzielHangar( this->Hangar::zajete_ - this->pobierzPojemnoscMaksymalnaHangaru(), o->pobierzPojemnoscMaksymalnaHangaru());
			if( zbHangar.pusty() || !o->Hangar::obiekty_.przeniesWszystkie(zbHangar) ){
				delete o;
				ilosc_+=ilosc;
				if( !Hangar::obiekty_.przeniesWszystkie(zbHangar) ){
					throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(-1),Tekst("Nieoczekiwany wyjatek"),Tekst("Wystapi³ nieoczekiwany wyjatek, który zaburzy³ dzia³anie aplikacji."));
				}
				this->przeliczZajeteMiejsceHangaru();
				return false;
			}
		}

		if(this->wolneMiejsceLadowni() < Fluktuacja(0.0)){
			zbLadownia = this->podzielLadownie( this->Ladownia::zajete_ - this->pobierzPojemnoscMaksymalnaLadowni(), o->pobierzPojemnoscMaksymalnaLadowni());
			if( zbLadownia.pusty() || !o->Ladownia::obiekty_.przeniesWszystkie(zbLadownia) ){
				delete o;
				ilosc_+=ilosc;
				if( !Hangar::obiekty_.przeniesWszystkie(zbHangar) || !Ladownia::obiekty_.przeniesWszystkie(zbLadownia) ){
					throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(-1),Tekst("Nieoczekiwany wyjatek"),Tekst("Wystapi³ nieoczekiwany wyjatek, który zaburzy³ dzia³anie aplikacji."));
				}
				this->przeliczZajeteMiejsceHangaru();
				this->przeliczZajeteMiejsceLadowni();
				return false;
			}
		}
		return o; 
	}
	return nullptr;
}	

bool Statek::polacz(const ObiektBazowy& obiektbazowy ){
	if(czyMoznaPolaczyc(obiektbazowy)){
		Statek & t = (Statek&)obiektbazowy;
		t.przeliczZajeteMiejsceLadowni();
		this->przeliczZajeteMiejsceLadowni();
		if((this->pobierzPojemnoscMaksymalnaLadowni()+t.pobierzPojemnoscMaksymalnaLadowni()) >= (t.pobierzZajeteMiejsceLadowni()+this->pobierzZajeteMiejsceLadowni())){
			if(ObiektBazowy::polacz(obiektbazowy)){
				if(Ladownia::polaczLadownie(t)){
					this->przeliczZajeteMiejsceLadowni();
					return true;
				}
				ilosc_ -= obiektbazowy.pobierzIlosc();
			}
		}
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

bool Statek::zapisz( TiXmlElement* wezel ) const {
	TiXmlElement* element = new TiXmlElement(WEZEL_XML_STATEK);
	wezel->LinkEndChild( element );
	return Obiekt::zapisz(element) && Ladownia::zapisz(element) && Hangar::zapisz(element);
}

bool Statek::odczytaj( TiXmlElement* wezel ) {
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
