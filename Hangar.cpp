#include "Hangar.h"
#include "Logger\Logger.h"
#include "definicjeWezlowXML.h"
#include "HangarInfo.h"
#include "Statek.h"
#include "MenedzerTranzakcji.h"
#include "Zlecenia.h"
#include "Aplikacja.h"

namespace SpEx{
	Hangar::Hangar(const STyp::Poziom& poziom, const STyp::Identyfikator& identyfikatorPlanety, const HangarInfo& hangarInfo)
		: PodstawoweParametry(wpisPoziom(poziom), POZIOM, identyfikatorPlanety), hangarInfo_(hangarInfo)
	{
	}

	Hangar::Hangar(const PodstawoweParametry& podstawoweParametry, const HangarInfo& hangarInfo)
		: PodstawoweParametry(podstawoweParametry), hangarInfo_(hangarInfo)
	{
	}
	
	STyp::Fluktuacja Hangar::wolneMiejsceHangaru() const{
		return STyp::Fluktuacja(1.0) - STyp::Fluktuacja(static_cast<float>((zajete_ / pobierzPojemnoscMaksymalnaHangaru())()));
	}

	bool Hangar::dodajStatekDoHangaru(const Item& obiekt){
		if (!obiekt.czyMoznaDodacDoHangaru()
			|| obiekt.pobierzPowierzchnie()() / obiekt.pobierzIlosc()() > pobierzPojemnoscMaksymalnaHangaru()()
			|| (obiekt.pobierzPowierzchnie() + zajete_) > pobierzPojemnoscMaksymalnaHangaru()){
			return false;
		}
		std::shared_ptr<Item> kopia = std::shared_ptr<Item>(obiekt.kopia());
		kopia->ustawIdentyfikatorPlanety(STyp::Identyfikator());
		bool rezultat = obiekty_.dodaj(kopia);
		przeliczZajeteMiejsceHangaru();
		return rezultat;
	}

	bool Hangar::dodajStatekDoHangaru(std::shared_ptr<Item> obiekt){
		if ( !obiekt || !obiekt->czyMoznaDodacDoHangaru()
			|| obiekt->pobierzPowierzchnie()() / obiekt->pobierzIlosc()() > pobierzPojemnoscMaksymalnaHangaru()()
			|| (obiekt->pobierzPowierzchnie() + zajete_) > pobierzPojemnoscMaksymalnaHangaru()){
			return false;
		}
		MenedzerTranzakcji tranzakcja;
		STyp::Identyfikator nowe(0);
		Hangar* hangar = this;

		tranzakcja.dodaj(std::make_shared<ZlecenieUstawIdentyfikatorPlanety>(nowe, static_cast<std::shared_ptr<PodstawoweParametry>>(obiekt)));

		tranzakcja.dodaj(std::make_shared< Zlecenie< Hangar::Zbiornik, std::shared_ptr< Item > > >(obiekty_, obiekt,
			[](Hangar::Zbiornik& h, std::shared_ptr< Item >& s)->bool{ return h.dodaj(s); },
			[](Hangar::Zbiornik& h, std::shared_ptr< Item >& s)->bool{ return false; }));

		tranzakcja.dodaj(std::make_shared< Zlecenie< Hangar, Hangar > >(*hangar, *hangar,
			[](Hangar& h, Hangar& s)->bool{ h.przeliczZajeteMiejsceHangaru(); return true; },
			[](Hangar& h, Hangar& s)->bool{ return false; }));

		return tranzakcja.wykonaj();
	}

	STyp::Powierzchnia Hangar::pobierzPojemnoscMaksymalnaHangaru() const{
		return hangarInfo_.pobierzMaksymalnaIloscPrzewozonychStatkow(*this);
	}

	STyp::Powierzchnia Hangar::pobierzPojemnoscJednostkowaHangaru() const{
		return hangarInfo_.pobierzMaksymalnaIloscPrzewozonychStatkow(*this);
	}

	bool Hangar::polaczHangar(Hangar& hangar){
		return obiekty_.przeniesWszystkie(hangar.obiekty_);
	}

	bool Hangar::polaczHangar(Zbiornik zbiornik){
		return obiekty_.przeniesWszystkie(zbiornik);
	}

	Hangar::Zbiornik Hangar::oproznijHangar(){
		Zbiornik tmp;
		tmp.przeniesWszystkie(obiekty_);
		przeliczZajeteMiejsceHangaru();
		return tmp;
	}

	STyp::Ilosc Hangar::pobierzIloscStatkow(const STyp::Identyfikator& klucz) const{
		auto element = obiekty_.pobierz(klucz);
		if (element)
			return element->pobierzIlosc();
		else
			return STyp::Ilosc(0);
	}

	std::shared_ptr<Hangar::Item> Hangar::wyjmijStatek(const STyp::Identyfikator& klucz, const STyp::Ilosc& ilosc){
		if (obiekty_.pusty() || ilosc == STyp::Ilosc())
			return nullptr;

		std::shared_ptr<Item> obiekt = obiekty_.pobierz(klucz);

		if (!obiekt)
			return nullptr;

		STyp::Ilosc tmp = obiekt->pobierzIlosc();
		
		if (ilosc > tmp)
			return nullptr;

		if (ilosc == tmp){
			obiekt = obiekty_.wyjmij(klucz);
			przeliczZajeteMiejsceHangaru();
			return obiekt;
		}

		std::shared_ptr<Item> czesc = std::shared_ptr<Item>(obiekt->podziel(ilosc));
		przeliczZajeteMiejsceHangaru();
		return czesc;
	}

	Hangar::ListaKluczy Hangar::pobierzListeIdentyfikatorowStatkow() const{
		return obiekty_.listaKluczy();
	}

	const Hangar::Zbiornik& Hangar::pobierzPrzewozoneStatki() const{
		return obiekty_;
	}

	Hangar::Zbiornik Hangar::podzielHangar(const STyp::Powierzchnia& minimum, const STyp::Powierzchnia& maksimum){
		Zbiornik zbiornik;

		STyp::Powierzchnia tymczasowaObjetosc(0.0);
		STyp::Powierzchnia tymczasoweMinimum(minimum);

		//Je¿eli objetoœæ czekiwana jest równa 0 to zwracamy pusty zbior obiektów
		if (maksimum == tymczasowaObjetosc)
			return Zbiornik();

		// Je¿eli objêtoœæ minimalna jest ujemna to j¹ zerujemy
		if (tymczasoweMinimum < tymczasowaObjetosc)
			tymczasoweMinimum = tymczasowaObjetosc;

		//Je¿eli objêtoœæ oczekiwana mniejsza od 0 lub objêtoœæ minimalna wiêksza od pojemnoœci 
		//lub objêtoœæ minimalna wiêksza od objêtoœci docelowej.
		if (maksimum < tymczasowaObjetosc || minimum > zajete_ || minimum > maksimum){
			return Zbiornik();
		}
		//Sortujemy zbiornik, tak aby w pierwszej kolejnoœci by³y przegl¹dane elementy o wiêkszym jednostkowym rozmiarze.
		Zbiornik kopia(obiekty_);
		std::vector< std::pair<STyp::Powierzchnia, STyp::Identyfikator> > posortowane;
		for (auto element : obiekty_)
			posortowane.emplace_back(element.second->pobierzPowierzchnieJednostkowa(), element.first);
		std::sort(posortowane.begin(), posortowane.end(), std::greater< std::pair<STyp::Powierzchnia, STyp::Identyfikator> >());

		/*
			Przechodzimy po elementach zbiornika i przepisujemy tyle ile siê da. Dopuszczamy dzielenie grup obiektów jeœli mo¿liwe.
			*/
		for (auto element : posortowane){
			STyp::Powierzchnia objElementu(obiekty_.pobierz(element.second)->pobierzPowierzchnie());
			if (objElementu + tymczasowaObjetosc <= maksimum){
				if (Zbiornik::przenies(element.second, kopia, zbiornik)){
					tymczasowaObjetosc += objElementu;
				}
			}
			else{
				STyp::Powierzchnia objPojedyncza(element.first);
				if (maksimum - tymczasowaObjetosc >= objPojedyncza){
					STyp::Ilosc liczbaElementow(floorl((maksimum() - tymczasowaObjetosc()) / objPojedyncza()));
					if (liczbaElementow >= STyp::Ilosc(1.0)){
						if (Zbiornik::przenies(element.second, liczbaElementow, kopia, zbiornik)){
							tymczasowaObjetosc += STyp::Powierzchnia(objPojedyncza() * liczbaElementow());
						}
					}
				}
			}
			if (tymczasowaObjetosc >= tymczasoweMinimum)
				break;
		}
		if (tymczasowaObjetosc >= tymczasoweMinimum){
			obiekty_ = std::move(kopia);
			przeliczZajeteMiejsceHangaru();
		}
		else{
			return Zbiornik();
		}
		return zbiornik;
	}

	const STyp::Powierzchnia& Hangar::pobierzZajeteMiejsceHangaru() const{
		return zajete_;
	}

	STyp::Powierzchnia Hangar::pobierzDostepneMiejsceHangaru() const{
		return pobierzPojemnoscMaksymalnaHangaru() - zajete_;
	}

	void Hangar::przeliczZajeteMiejsceHangaru(){
		zajete_ = STyp::Powierzchnia(0);
		for (auto element : obiekty_){
			zajete_ += element.second->pobierzPowierzchnie();
		}
	}

	STyp::Masa Hangar::pobierzMaseZawartosciHangaru()const {
		STyp::Masa masa(0);
		for (auto element : obiekty_){
			masa += element.second->pobierzMase();
		}
		return masa;
	}

	bool Hangar::zapisz(XmlBO::ElementWezla wezel) const {
		XmlBO::ElementWezla element = wezel->tworzElement(WEZEL_XML_HANGAR);
		if (zajete_ < STyp::Powierzchnia(0))
			return false;
		element->tworzAtrybut(ATRYBUT_XML_ZAJETE_MIEJSCE, zajete_.napis().c_str());
		for (auto o : obiekty_){
			if (!o.second->zapisz(element))
				return false;
		}
		return true;
	}

	bool Hangar::odczytaj(XmlBO::ElementWezla wezel) {

		XmlBO::WczytajAtrybut<THROW>(wezel, ATRYBUT_XML_ZAJETE_MIEJSCE, zajete_);
		if (zajete_ < STyp::Powierzchnia(0))
			SPar::ParserUtils::generujWyjatekBleduStruktury(wezel);

		Gra& gra = Aplikacja::pobierzInstancje().pobierzGre();

		XmlBO::ForEach<THROW>(wezel, WEZEL_XML_STATEK, XmlBO::OperacjaWezla(
			[&](XmlBO::ElementWezla element)->bool{
			std::shared_ptr<Statek> obiekt = gra.tworzStatek(element);
			if (!obiekt || !obiekt->odczytaj(element)){
				SPar::ParserUtils::generujWyjatekBleduStruktury(element);
			}
			obiekty_.dodaj(obiekt);
			return true;
		}));

		return true;
	}

	std::string Hangar::napis() const{
		SLog::Logger str(NAZWAKLASY(Hangar));
		str.dodajPole(NAZWAPOLA(zajete_), zajete_);
		str.dodajPole(NAZWAPOLA(obiekty_), obiekty_);
		str.dodajPole(NAZWAPOLA(hangarInfo_), hangarInfo_);
		return str.napis();
	}
}
