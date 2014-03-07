#include "Info.h"
#include "definicjeWezlowXML.h"
#include "Logger\Logger.h"
#include "Utils.h"

namespace SpEx {

	Info::Info(const STyp::Tekst& nazwa, const STyp::Tekst& opis, const STyp::Identyfikator& identyfikator)
		: identyfikator_(identyfikator), nazwa_(nazwa), opis_(opis)
	{
	}

	Info::Info(XmlBO::ElementWezla wezel){
		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_IDENTYFIKATOR, identyfikator_);
		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_NAZWA, nazwa_);
		auto tablicaZnakow = wezel->pobierzTekst();
		if (tablicaZnakow){
			ustawOpis(std::string(tablicaZnakow));
		}else{
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

	std::string Info::napis() const{
		SLog::Logger str(NAZWAKLASY(Info));
		str.dodajPole(NAZWAPOLA(identyfikator_), identyfikator_);
		str.dodajPole(NAZWAPOLA(nazwa_), nazwa_);
		str.dodajPole(NAZWAPOLA(opis_), opis_);
		return str.napis();
	}
}
