#include "Statek.h"
#include "StatekInfo.h"
#include "Logger.h"
#include "DefinicjeWezlowXML.h"

Statek::Statek( const Ilosc& ilosc, const Poziom& poziom, const Identyfikator& identyfikatorPlanety, const StatekInfo& statekInfo )
	: PodstawoweParametry(poziom, identyfikatorPlanety), Obiekt( ilosc, poziom, identyfikatorPlanety, statekInfo ), JednostkaAtakujaca(poziom,identyfikatorPlanety,statekInfo),
	JednostkaLatajaca(poziom,identyfikatorPlanety,statekInfo), Ladownia(poziom,identyfikatorPlanety,statekInfo), statekinfo_(statekInfo)
{
}

Statek::Statek( const Ilosc& ilosc, const PodstawoweParametry& podstawoweParametry, const StatekInfo& statekInfo )
	: PodstawoweParametry(podstawoweParametry), Obiekt( ilosc, podstawoweParametry, statekInfo ), JednostkaAtakujaca(podstawoweParametry,statekInfo),
	JednostkaLatajaca(podstawoweParametry,statekInfo), Ladownia(podstawoweParametry,statekInfo), statekinfo_(statekInfo)
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

Statek* Statek::podziel( const Ilosc& ilosc ){
	if( ilosc_>ilosc ){
		Statek* o = new Statek( ilosc , *this, this->statekinfo_ );
		ilosc_-=ilosc;
		this->przeliczZajeteMiejsce();
		if(this->wolneMiejsce() < Fluktuacja(0.0)){
			Zbiornik zb = this->podzielLadownie( this->zajete_ - this->pobierzPojemnoscMaksymalna(), o->pobierzPojemnoscMaksymalna());
			if( zb.pusty() || !o->obiekty_.przeniesWszystkie(zb) ){
				delete o;
				ilosc_+=ilosc;
				if( !obiekty_.przeniesWszystkie(zb) ){
					throw OgolnyWyjatek(EXCEPTION_PLACE,Identyfikator(-1),Tekst("Nieoczekiwany wyjatek"),Tekst("Wystapi³ nieoczekiwany wyjatek, który zaburzy³ dzia³anie aplikacji."));
				}
				this->przeliczZajeteMiejsce();
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
		t.przeliczZajeteMiejsce();
		this->przeliczZajeteMiejsce();
		if((this->pobierzPojemnoscMaksymalna()+t.pobierzPojemnoscMaksymalna()) >= (t.pobierzZajeteMiejsce()+this->pobierzZajeteMiejsce())){
			if(ObiektBazowy::polacz(obiektbazowy)){
				if(Ladownia::polacz(t)){
					this->przeliczZajeteMiejsce();
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

Objetosc Statek::pobierzPojemnoscMaksymalna() const{
	return Ladownia::pobierzPojemnoscMaksymalna()*pobierzIlosc();
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

bool Statek::czyMoznaDodacDoLadownii( const Ladownia& ladownia ) const{
	return ladownia.czyMoznaDodacDoLadownii(*this);
}

const StatekInfo& Statek::pobierzStatekInfo() const{
	return statekinfo_;
}

bool Statek::zapisz( TiXmlElement* wezel ) const {
	TiXmlElement* element = new TiXmlElement(WEZEL_XML_STATEK);
	wezel->LinkEndChild( element );
	return Obiekt::zapisz(element) && Ladownia::zapisz(element);
}

bool Statek::odczytaj( TiXmlElement* wezel ) {
	return Obiekt::odczytaj(wezel) && Ladownia::odczytaj(wezel->FirstChildElement(WEZEL_XML_LADOWNIA));
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
	str.dodajPole(NAZWAKLASY(StatekInfo)+"ID",statekinfo_.pobierzIdentyfikator());
	return str.napis();
}
