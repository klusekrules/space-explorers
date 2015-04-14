#include "Info.h"
#include "Utils\DefinicjeWezlowXML.h"
#include "Logger\Logger.h"
#include "Utils\StackThrow.h"
#include "Kontroler\Aplikacja.h"
#include "Kontroler\Zarzadca\ZarzadcaZasobow.h"

namespace SpEx {

	Info::Info(const STyp::Identyfikator& typ, XmlBO::ElementWezla wezel)
		: typ_(typ)
	{
		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_IDENTYFIKATOR, identyfikator_);
		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_NAZWA, nazwa_);
		STyp::Tekst nazwaObrazka;
		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_ADRES_OBRAZKA, nazwaObrazka);

		idObrazka_ = Aplikacja::pobierzInstancje().pobierzZarzadceZasobow().pobierzIdentyfikator(nazwaObrazka());
		auto tablicaZnakow = wezel->pobierzTekst();
		if (tablicaZnakow){
			ustawOpis(std::string(tablicaZnakow));
		}
		else{
			ustawOpis(std::string());
		}
	}

	const STyp::Identyfikator& Info::pobierzIdentyfikator() const{
		return identyfikator_;
	}

	void Info::ustawIdentyfikator(const STyp::Identyfikator& identyfikator){
		identyfikator_ = identyfikator;
	}

	const STyp::Tekst& Info::pobierzNazwe() const{
		return nazwa_;
	}

	void Info::ustawNazwe(const STyp::Tekst& nazwa){
		nazwa_ = nazwa;
	}

	const STyp::Tekst& Info::pobierzOpis() const{
		return opis_;
	}

	void Info::ustawOpis(const STyp::Tekst& opis){
		opis_ = opis;
	}

	const STyp::Identyfikator& Info::pobierzIdentyfikatorObrazka() const{
		return idObrazka_;
	}

	std::string Info::napis() const{
		SLog::Logger str(NAZWAKLASY(Info));
		str.dodajPole(NAZWAPOLA(typ_), typ_);
		str.dodajPole(NAZWAPOLA(identyfikator_), identyfikator_);
		str.dodajPole(NAZWAPOLA(nazwa_), nazwa_);
		str.dodajPole(NAZWAPOLA(opis_), opis_);
		str.dodajPole(NAZWAPOLA(idObrazka_), idObrazka_);
		return str.napis();
	}
}
