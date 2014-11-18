#include "Licznik.h"
#include "DefinicjeWezlowXML.h"
#include "Logger\Logger.h"
#include "Utils.h"

namespace SpEx{
	Licznik::Licznik(const STyp::Identyfikator& identyfikator, const STyp::Ilosc& wartoscPoczatkowa)
		: identyfikator_(identyfikator),wartoscLicznika_(wartoscPoczatkowa)
	{
	}
	
	const STyp::Identyfikator& Licznik::pobierzIdentyfikator()const{
		return identyfikator_;
	}

	STyp::Ilosc Licznik::operator()(){
		return wartoscLicznika_++;
	}

	STyp::Ilosc Licznik::pobierzWartosc()const{
		return wartoscLicznika_;
	}

	void Licznik::resetujWartosc(){
		wartoscLicznika_ = STyp::Ilosc(0);
	}

	void Licznik::ustawWartosc(const STyp::Ilosc& wartosc){
		wartoscLicznika_ = wartosc;
	}

	bool Licznik::zapisz(XmlBO::ElementWezla wezel) const{
		XmlBO::ElementWezla dziecko = wezel->tworzElement(WEZEL_XML_LICZNIK);
		if (dziecko == nullptr)
			return false;
		return dziecko->tworzAtrybut(ATRYBUT_XML_ILOSC, std::to_string(wartoscLicznika_()).c_str()) != nullptr && dziecko->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, std::to_string(identyfikator_()).c_str()) != nullptr;
	}

	bool Licznik::odczytaj(XmlBO::ElementWezla wezel){
		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_IDENTYFIKATOR, identyfikator_);
		return XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_ILOSC, wartoscLicznika_);
	}

	std::string Licznik::napis()const{
		SLog::Logger str(NAZWAKLASY(Licznik));
		str.dodajPole(NAZWAPOLA(wartoscLicznika_), wartoscLicznika_);
		return str.napis();
	}
}