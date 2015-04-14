#include "Statek.h"
#include "StatekInfo.h"
#include "Logger\Logger.h"
#include "Utils\DefinicjeWezlowXML.h"
#include "Utils\Tranzakcje\MenedzerTranzakcji.h"
#include "Utils\Tranzakcje\Zlecenia.h"

namespace SpEx{
	Statek::Statek(const STyp::Ilosc& ilosc, const STyp::Identyfikator& identyfikatorPlanety, const StatekInfo& statekInfo)
		: PodstawoweParametry(wpisIlosc(ilosc), statekInfo.pobierzTypAtrybutu(), identyfikatorPlanety),
		Obiekt(PodstawoweParametry(wpisIlosc(ilosc), statekInfo.pobierzTypAtrybutu(), identyfikatorPlanety), statekInfo),
		JednostkaAtakujaca(PodstawoweParametry(wpisIlosc(ilosc), statekInfo.pobierzTypAtrybutu(), identyfikatorPlanety), statekInfo),
		JednostkaLatajaca(PodstawoweParametry(wpisIlosc(ilosc), statekInfo.pobierzTypAtrybutu(), identyfikatorPlanety), statekInfo),
		Ladownia(PodstawoweParametry(wpisIlosc(ilosc), statekInfo.pobierzTypAtrybutu(), identyfikatorPlanety), statekInfo),
		Hangar(PodstawoweParametry(wpisIlosc(ilosc), statekInfo.pobierzTypAtrybutu(), identyfikatorPlanety), statekInfo),
		statekinfo_(statekInfo)
	{
	}

	Statek::Statek(const PodstawoweParametry& podstawoweParametry, const StatekInfo& statekInfo)
		: PodstawoweParametry(podstawoweParametry), Obiekt(podstawoweParametry, statekInfo), JednostkaAtakujaca(podstawoweParametry, statekInfo),
		JednostkaLatajaca(podstawoweParametry, statekInfo), Ladownia(podstawoweParametry, statekInfo), Hangar(podstawoweParametry, statekInfo), statekinfo_(statekInfo)
	{
	}

	STyp::ZuzyciePaliwa Statek::wyliczZuzyciePaliwa(const STyp::Dystans& dystans, const STyp::Predkosc& predkosc) const {
		return STyp::ZuzyciePaliwa(pobierzIlosc()() * JednostkaLatajaca::wyliczZuzyciePaliwa(dystans, predkosc)());
	}

	Statek* Statek::kopia() const{
		return new Statek(*this);
	}

	bool Statek::polacz(const Obiekt& obiekt){
		if (czyMoznaPolaczyc(obiekt)){
			Statek & t = (Statek&)obiekt;
			Statek* statek = this;
			MenedzerTranzakcji tranzakcja;

			tranzakcja.dodaj(std::make_shared< Zlecenie< const STyp::Ilosc, PodstawoweParametry > >(obiekt.pobierzIlosc(), *this,
				[&statek, &t](const STyp::Ilosc& ilosc, PodstawoweParametry& atrybut)->bool{ atrybut.wzrostAtrybutu(PodstawoweParametry::wpisIlosc(ilosc)); statek->przeliczZajeteMiejsceLadowni(); statek->przeliczZajeteMiejsceHangaru(); t.przeliczZajeteMiejsceLadowni(); t.przeliczZajeteMiejsceHangaru(); return true; },
				[&statek, &t](const STyp::Ilosc& ilosc, PodstawoweParametry& atrybut)->bool{ atrybut.wzrostAtrybutu(PodstawoweParametry::wpisIlosc(-ilosc)); statek->przeliczZajeteMiejsceLadowni(); statek->przeliczZajeteMiejsceHangaru(); t.przeliczZajeteMiejsceLadowni(); t.przeliczZajeteMiejsceHangaru(); return true; }));

			tranzakcja.dodaj(std::make_shared< Zlecenie< Statek, Statek > >(t, *statek,
				[](Statek& o, Statek& s)->bool{ return s.pobierzPojemnoscMaksymalnaLadowni() >= (o.pobierzZajeteMiejsceLadowni() + s.pobierzZajeteMiejsceLadowni()); },
				[](Statek& o, Statek& s)->bool{ return true; }));

			tranzakcja.dodaj(std::make_shared< Zlecenie< Statek, Statek > >(t, *statek,
				[](Statek& o, Statek& s)->bool{ return s.pobierzPojemnoscMaksymalnaHangaru() >= (o.pobierzZajeteMiejsceHangaru() + s.pobierzZajeteMiejsceHangaru()); },
				[](Statek& o, Statek& s)->bool{ return true; }));

			tranzakcja.dodaj(std::make_shared< Zlecenie< Statek, Statek > >(t, *statek,
				[](Statek& o, Statek& s)->bool{ return s.polaczLadownie(o); },
				[](Statek& o, Statek& s)->bool{ return false; }));

			tranzakcja.dodaj(std::make_shared< Zlecenie< Statek, Statek > >(t, *statek,
				[](Statek& o, Statek& s)->bool{ return s.polaczHangar(o); },
				[](Statek& o, Statek& s)->bool{ return false; }));

			tranzakcja.dodaj(std::make_shared< Zlecenie< Statek, Statek > >(*statek, *statek,
				[](Statek& o, Statek& s)->bool{ s.przeliczZajeteMiejsceLadowni(); s.przeliczZajeteMiejsceHangaru(); return true; },
				[](Statek& o, Statek& s)->bool{ return true; }));

			return tranzakcja.wykonaj();
		}
		return false;
	}
	
	STyp::Powierzchnia Statek::pobierzPowierzchnie()const{
		return statekinfo_.pobierzPowierzchnie(*this);
	}

	STyp::Powierzchnia Statek::pobierzPowierzchnieJednostkowa()const{
		return statekinfo_.pobierzPowierzchnie(PodstawoweParametry(STyp::Ilosc(1), pobierzIdentyfikatorPlanety()));
	}

	STyp::Masa Statek::pobierzMase()const{
		return statekinfo_.pobierzMase(*this) + Ladownia::pobierzMaseZawartosciLadowni() + Statek::pobierzMasaSilnika() + Hangar::pobierzMaseZawartosciHangaru();
	}

	bool Statek::czyMoznaDodacDoHangaru() const{
		return statekinfo_.czyMoznaDodacDoHangaru();
	}

	Statek* Statek::podziel(const STyp::Ilosc& ilosc){
		auto ilosc_ = pobierzIlosc();
		if (ilosc_ > ilosc){
			MenedzerTranzakcji tranzakcja;
			Statek* o = new Statek(ilosc,pobierzIdentyfikatorPlanety(), this->statekinfo_);
			Statek* statek = this;
			tranzakcja.dodaj(std::make_shared< Zlecenie< const STyp::Ilosc, STyp::Ilosc > >(ilosc, ilosc_,
				[&statek](const STyp::Ilosc& ilosc, STyp::Ilosc& ilosc_s)->bool{ statek->ustawAtrybut(wpisIlosc(ilosc_s - ilosc)); return true; },
				[&statek](const STyp::Ilosc& ilosc, STyp::Ilosc& ilosc_s)->bool{ statek->ustawAtrybut(wpisIlosc(ilosc_s)); statek->przeliczZajeteMiejsceLadowni(); statek->przeliczZajeteMiejsceHangaru(); return true; }));

			tranzakcja.dodaj(std::make_shared< Zlecenie< Statek, Statek > >(*statek, *statek,
				[](Statek& o, Statek& s)->bool{ o.przeliczZajeteMiejsceLadowni(); o.przeliczZajeteMiejsceHangaru(); return true; },
				[](Statek& o, Statek& s)->bool{ return true; }));

			Hangar::Zbiornik zbHangar;
			Ladownia::Zbiornik zbLadownia;

			tranzakcja.dodaj(std::make_shared< Zlecenie< Statek, Statek > >(*o, *statek,
				[&zbHangar](Statek& o, Statek& s)->bool{
				if (s.wolneMiejsceHangaru() < STyp::Fluktuacja(0.0)){
					zbHangar = s.podzielHangar(s.Hangar::zajete_ - s.pobierzPojemnoscMaksymalnaHangaru(), o.pobierzPojemnoscMaksymalnaHangaru());
					return !zbHangar.pusty();
				}
				return true;
			},
				[&zbHangar](Statek& o, Statek& s)->bool{ return s.Hangar::obiekty_.przeniesWszystkie(zbHangar); }));

			tranzakcja.dodaj(std::make_shared< Zlecenie< Statek, Statek > >(*o, *statek,
				[&zbHangar](Statek& o, Statek& s)->bool{ return o.Hangar::obiekty_.przeniesWszystkie(zbHangar); },
				[&zbHangar](Statek& o, Statek& s)->bool{ return true; }));

			tranzakcja.dodaj(std::make_shared< Zlecenie< Statek, Statek > >(*o, *statek,
				[&zbLadownia](Statek& o, Statek& s)->bool{
				if (s.wolneMiejsceLadowni() < STyp::Fluktuacja(0.0)){
					zbLadownia = s.podzielLadownie(s.Ladownia::zajete_ - s.pobierzPojemnoscMaksymalnaLadowni(), o.pobierzPojemnoscMaksymalnaLadowni());
					return !zbLadownia.pusty();
				}
				return true;
			},
				[&zbLadownia](Statek& o, Statek& s)->bool{ return s.Ladownia::obiekty_.przeniesWszystkie(zbLadownia); }));

			tranzakcja.dodaj(std::make_shared< Zlecenie< Statek, Statek > >(*o, *statek,
				[&zbLadownia](Statek& o, Statek& s)->bool{ return o.Ladownia::obiekty_.przeniesWszystkie(zbLadownia); },
				[&zbLadownia](Statek& o, Statek& s)->bool{ return true; }));

			if (tranzakcja.wykonaj())
				return o;
		}
		return nullptr;
	}

	STyp::Obrazenia Statek::pobierzAtak() const{
		return STyp::Obrazenia(JednostkaAtakujaca::pobierzAtak()() * pobierzIlosc()());
	}

	STyp::Obrazenia Statek::pobierzPancerz() const{
		return STyp::Obrazenia(JednostkaAtakujaca::pobierzPancerz()() * pobierzIlosc()());
	}

	STyp::Obrazenia Statek::pobierzOslone() const{
		return STyp::Obrazenia(JednostkaAtakujaca::pobierzOslone()() * pobierzIlosc()());
	}

	STyp::Objetosc Statek::pobierzPojemnoscMaksymalnaLadowni() const{
		return Ladownia::pobierzPojemnoscMaksymalnaLadowni()()*pobierzIlosc()();
	}

	STyp::Powierzchnia Statek::pobierzPojemnoscMaksymalnaHangaru() const{
		return Hangar::pobierzPojemnoscMaksymalnaHangaru()()*pobierzIlosc()();
	}

	STyp::Masa Statek::pobierzMasaSilnika()const{
		return STyp::Masa(JednostkaLatajaca::pobierzMasaSilnika()()* pobierzIlosc()());
	}

	STyp::ZuzyciePaliwa Statek::pobierzJednostkoweZuzyciePaliwa()const{
		return STyp::ZuzyciePaliwa(JednostkaLatajaca::pobierzJednostkoweZuzyciePaliwa()()*pobierzIlosc()());
	}

	const StatekInfo& Statek::pobierzStatekInfo() const{
		return statekinfo_;
	}

	bool Statek::zapisz(XmlBO::ElementWezla wezel) const {
		XmlBO::ElementWezla element = wezel->tworzElement(WEZEL_XML_STATEK);
		return Obiekt::zapisz(element) && Ladownia::zapisz(element) && Hangar::zapisz(element);
	}

	bool Statek::odczytaj(XmlBO::ElementWezla wezel) {
		return Obiekt::odczytaj(wezel) && Ladownia::odczytaj(wezel->pobierzElement(WEZEL_XML_LADOWNIA)) && Hangar::odczytaj(wezel->pobierzElement(WEZEL_XML_HANGAR));
	}

	STyp::Masa Statek::calkowitaMasaJednostki() const{
		return pobierzMase();
	}

	std::string Statek::napis() const{
		SLog::Logger str(NAZWAKLASY(Statek));
		str.dodajKlase(Obiekt::napis());
		str.dodajKlase(JednostkaAtakujaca::napis());
		str.dodajKlase(JednostkaLatajaca::napis());
		str.dodajKlase(Ladownia::napis());
		str.dodajKlase(Hangar::napis());
		str.dodajPole(NAZWAKLASY(StatekInfo), statekinfo_.pobierzIdentyfikator());
		return str.napis();
	}
}
