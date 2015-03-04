#include "Ladownia.h"
#include "LadowniaInfo.h"
#include "Statek.h"
#include "Surowce.h"
#include "Aplikacja.h"
#include "Utils.h"
#include "DefinicjeWezlowXML.h"
#include <algorithm>
#include <functional>
#include "MenedzerTranzakcji.h"
#include "Zlecenia.h"
#include "Gra.h"
#include "Utils.h"
#include "StackThrow.h"

namespace SpEx{
	Ladownia::Ladownia(const STyp::Ilosc& ilosc, const STyp::Identyfikator& identyfikatorPlanety, const LadowniaInfo& ladowniaInfo)
		: PodstawoweParametry(wpisIlosc(ilosc), ILOSC, identyfikatorPlanety), obiekty_(), zajete_(), ladowniaInfo_(ladowniaInfo)
	{
	}

	Ladownia::Ladownia(const PodstawoweParametry& podstawoweParametry, const LadowniaInfo& ladowniaInfo)
		: PodstawoweParametry(podstawoweParametry), obiekty_(), zajete_(), ladowniaInfo_(ladowniaInfo)
	{
	}
	
	STyp::Fluktuacja Ladownia::wolneMiejsceLadowni() const{
		return STyp::Fluktuacja(1.0) - STyp::Fluktuacja( static_cast<float>( (zajete_ / pobierzPojemnoscMaksymalnaLadowni() )() ));
	}

	STyp::Ilosc Ladownia::pobierzIloscObiektowLadowni(const STyp::Identyfikator& klucz) const{
		auto element = obiekty_.pobierz(klucz);
		if (element)
			return element->pobierzIlosc();
		else
			return STyp::Ilosc(0);
	}

	bool Ladownia::polaczLadownie(Ladownia& ladownia){
		return obiekty_.przeniesWszystkie(ladownia.obiekty_);
	}

	bool Ladownia::polaczLadownie(Zbiornik zbiornik){
		return obiekty_.przeniesWszystkie(zbiornik);
	}

	//Tranzakcyjna
	bool Ladownia::dodajObiektDoLadowni(const Item& obiekt){
		if (!obiekt.czyTypPrzyrostowy()){
			return false;
		}
		if (obiekt.pobierzObjetosc()() / obiekt.pobierzIlosc()() > pobierzPojemnoscMaksymalnaLadowni()() || (obiekt.pobierzObjetosc() + zajete_) > pobierzPojemnoscMaksymalnaLadowni()){
			return false;
		}
		std::shared_ptr<Surowce> kopia = std::shared_ptr<Surowce>(obiekt.kopia());
		kopia->ustawIdentyfikatorPlanety(STyp::Identyfikator());
		bool rezultat = obiekty_.dodaj(kopia);
		przeliczZajeteMiejsceLadowni();
		return rezultat;
	}

	//Tranzakcyjna
	bool Ladownia::dodajObiektDoLadowni(std::shared_ptr<Item> obiekt){
		if (!obiekt
			|| !obiekt->czyTypPrzyrostowy()
			|| obiekt->pobierzObjetosc()() / obiekt->pobierzIlosc()() > ladowniaInfo_.pobierzPojemnoscMaksymalna(*this)()
			|| (obiekt->pobierzObjetosc() + zajete_) > pobierzPojemnoscMaksymalnaLadowni()){
			return false;
		}
		MenedzerTranzakcji tranzakcja;
		STyp::Identyfikator nowe(0);
		Ladownia* ladownia = this;

		tranzakcja.dodaj(std::make_shared<ZlecenieUstawIdentyfikatorPlanety>(nowe, static_cast<std::shared_ptr<PodstawoweParametry>>(obiekt)));

		tranzakcja.dodaj(std::make_shared< Zlecenie< Ladownia::Zbiornik, std::shared_ptr< Item > > >(obiekty_, obiekt,
			[](Ladownia::Zbiornik& h, std::shared_ptr< Item >& s)->bool{ return h.dodaj(s); },
			[](Ladownia::Zbiornik& h, std::shared_ptr< Item >& s)->bool{ return false; }));

		tranzakcja.dodaj(std::make_shared< Zlecenie< Ladownia, Ladownia > >(*ladownia, *ladownia,
			[](Ladownia& h, Ladownia& s)->bool{ h.przeliczZajeteMiejsceLadowni(); return true; },
			[](Ladownia& h, Ladownia& s)->bool{ return false; }));

		return tranzakcja.wykonaj();
	}

	//Tranzakcyjna
	Ladownia::Zbiornik Ladownia::oproznijLadownie(){
		Zbiornik tmp;
		tmp.przeniesWszystkie(obiekty_);
		przeliczZajeteMiejsceLadowni();
		return tmp;
	}

	std::shared_ptr<Ladownia::Item> Ladownia::wyjmijObiektZLadowni(const STyp::Identyfikator& klucz, const STyp::Ilosc& ilosc){
		if (obiekty_.pusty() || ilosc == STyp::Ilosc())
			return nullptr;

		std::shared_ptr<Ladownia::Item> obiekt = obiekty_.pobierz(klucz);

		if (!obiekt || ilosc > obiekt->pobierzIlosc())
			return nullptr;

		if (ilosc == obiekt->pobierzIlosc()){
			obiekt = obiekty_.wyjmij(klucz);
			przeliczZajeteMiejsceLadowni();
			return obiekt;
		}

		std::shared_ptr<Ladownia::Item> czesc = std::shared_ptr<Ladownia::Item>(obiekt->podziel(ilosc));
		przeliczZajeteMiejsceLadowni();
		return czesc;
	}

	/* Zwrócony zbiornik ma objêtoœæ z przedzia³u  < min , max >  */
	//Tranzakcyjna
	Ladownia::Zbiornik Ladownia::podzielLadownie(const STyp::Objetosc& minimum, const STyp::Objetosc& maksimum){
		Zbiornik zbiornik;

		STyp::Objetosc tymczasowaObjetosc(0.0);
		STyp::Objetosc tymczasoweMinimum(minimum);

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
		std::vector< std::pair<STyp::Objetosc, STyp::Identyfikator> > posortowane;
		for (auto element : obiekty_)
			posortowane.push_back(std::make_pair(element.second->pobierzObjetoscJednostkowa(), element.first));
		std::sort(posortowane.begin(), posortowane.end(), std::greater< std::pair<STyp::Objetosc, STyp::Identyfikator> >());
		/*
			Przechodzimy po elementach zbiornika i przepisujemy tyle ile siê da. Dopuszczamy dzielenie grup obiektów jeœli mo¿liwe.
			*/
		for (auto element : posortowane){
			STyp::Objetosc objElementu(obiekty_.pobierz(element.second)->pobierzObjetosc());
			if (objElementu + tymczasowaObjetosc <= maksimum){
				if (Zbiornik::przenies(element.second, kopia, zbiornik)){
					tymczasowaObjetosc += objElementu;
				}
			}
			else{
				STyp::Objetosc objPojedyncza(element.first);
				if (maksimum - tymczasowaObjetosc >= objPojedyncza){
					STyp::Ilosc liczbaElementow(floorl((maksimum() - tymczasowaObjetosc()) / objPojedyncza()));
					if (liczbaElementow >= STyp::Ilosc(1.0)){
						if (Zbiornik::przenies(element.second, liczbaElementow, kopia, zbiornik)){
							tymczasowaObjetosc += STyp::Objetosc(objPojedyncza() * liczbaElementow());
						}
					}
				}
			}
			if (tymczasowaObjetosc >= tymczasoweMinimum)
				break;
		}
		if (tymczasowaObjetosc >= tymczasoweMinimum){
			obiekty_ = std::move(kopia);
			przeliczZajeteMiejsceLadowni();
		}
		else{
			return Zbiornik();
		}
		return zbiornik;
	}

	void Ladownia::przeliczZajeteMiejsceLadowni(){
		zajete_ = STyp::Objetosc(0);
		for (auto element : obiekty_){
			zajete_ += element.second->pobierzObjetosc();
		}
	}

	STyp::Masa Ladownia::pobierzMaseZawartosciLadowni()const {
		STyp::Masa masa(0);
		for (auto element : obiekty_){
			masa += element.second->pobierzMase();
		}
		return masa;
	}

	Ladownia::ListaKluczy Ladownia::pobierzListeIdentyfikatorowObiektowLadowni() const{
		return obiekty_.listaKluczy();
	}

	const Ladownia::Zbiornik& Ladownia::pobierzPrzewozoneObiektyLadowni() const{
		return obiekty_;
	}

	const STyp::Objetosc& Ladownia::pobierzZajeteMiejsceLadowni() const{
		return zajete_;
	}

	STyp::Objetosc Ladownia::pobierzDostepneMiejsceLadowni() const{
		return pobierzPojemnoscMaksymalnaLadowni() - zajete_;
	}

	STyp::Objetosc Ladownia::pobierzPojemnoscMaksymalnaLadowni() const{
		return ladowniaInfo_.pobierzPojemnoscMaksymalna(*this);
	}

	STyp::Objetosc Ladownia::pobierzPojemnoscJednostkowaLadowni() const{
		return ladowniaInfo_.pobierzPojemnoscMaksymalna(*this);
	}

	bool Ladownia::zapisz(XmlBO::ElementWezla wezel) const {
		XmlBO::ElementWezla element = wezel->tworzElement(WEZEL_XML_LADOWNIA);
		if (zajete_ < STyp::Objetosc(0))
			return false;
		element->tworzAtrybut(ATRYBUT_XML_ZAJETE_MIEJSCE, std::to_string(zajete_()).c_str());
		for (auto o : obiekty_){
			if (!o.second->zapisz(element))
				return false;
		}
		return true;
	}

	bool Ladownia::odczytaj(XmlBO::ElementWezla wezel) {

		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_ZAJETE_MIEJSCE, zajete_);
		if (zajete_ < STyp::Objetosc(0))
			return false;

		auto& gra = Aplikacja::pobierzInstancje().pobierzGre();

		XmlBO::ForEach<STACKTHROW>(wezel, WEZEL_XML_SUROWCE, XmlBO::OperacjaWezla(
			[&](XmlBO::ElementWezla element)->bool{
			auto obiekt = gra.tworzObiekt<Surowce>(element);
			if (!obiekt || !obiekt->odczytaj(element)){
				Utils::generujWyjatekBleduStruktury(element);
			}
			obiekty_.dodaj(obiekt);
			return true;
		}));
		return true;
	}

	std::string Ladownia::napis() const{
		SLog::Logger str(NAZWAKLASY(Ladownia));
		str.dodajPole(NAZWAPOLA(zajete_), zajete_);
		str.dodajPole(NAZWAPOLA(obiekty_), obiekty_);
		return str.napis();
	}
}
