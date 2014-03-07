#include "ZmianaAgregacja.h"
#include "Logger\Logger.h"
#include "ZmianaStaleXml.h"

namespace SZmi{
	ZmianaAgregacja::ZmianaAgregacja(XmlBO::ElementWezla wezel)
	{
		if (wezel && fabryka_){
			XmlBO::ElementWezla wezelNastepny = XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel, XML_WEZEL_ZMIANA, XML_ATRYBUT_ZMIANA_FOR, XML_WARTOSC_ATRYBUTU_ZMIANA_NASTEPNY);
			if (!wezelNastepny)
				SPar::ParserUtils::generujWyjatekBleduStruktury(wezel, STyp::Tekst());
			nastepna_ = fabryka_->Tworz(wezelNastepny);
			if (!nastepna_)
				SPar::ParserUtils::generujWyjatekBleduStruktury(wezelNastepny, STyp::Tekst());

			XmlBO::ElementWezla dziecko = XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel, XML_WEZEL_ZMIANA, XML_ATRYBUT_ZMIANA_FOR, XML_WARTOSC_ATRYBUTU_ZMIANA_BRAT);
			if (!dziecko)
				SPar::ParserUtils::generujWyjatekBleduStruktury(wezel, STyp::Tekst());
			for (; dziecko; dziecko = XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel, XML_WEZEL_ZMIANA, XML_ATRYBUT_ZMIANA_FOR, XML_WARTOSC_ATRYBUTU_ZMIANA_BRAT, dziecko)){
				auto element = fabryka_->Tworz(dziecko);
				if (element)
					listaZmian_.push_back(element);
				else
					SPar::ParserUtils::generujWyjatekBleduStruktury(dziecko, STyp::Tekst());
			}
		}
	}

	ZmianaInterfejs* ZmianaAgregacja::TworzZmianaAgregacja(XmlBO::ElementWezla wezel){
		return new ZmianaAgregacja(wezel);
	}

	ZmianaAgregacja* ZmianaAgregacja::Kopia()const{
		return new ZmianaAgregacja(*this);
	}

	ZmianaAgregacja::ZmianaAgregacja(const ZmianaAgregacja& obiekt)
		: nastepna_(nullptr)
	{
		this->operator=(obiekt);
	}

	ZmianaAgregacja& ZmianaAgregacja::operator=(const ZmianaAgregacja& obiekt){
		if (obiekt.nastepna_)
			nastepna_ = std::shared_ptr<ZmianaInterfejs>(obiekt.nastepna_->Kopia());
		else
			nastepna_ = nullptr;
		for (auto element : obiekt.listaZmian_){
			if (element)
				listaZmian_.push_back(std::shared_ptr<ZmianaInterfejs>(element->Kopia()));
		}
		return *this;
	}

	STyp::Wartosc ZmianaAgregacja::policzWartosc(const STyp::Wartosc& wartosc, const STyp::Poziom& poziom, const STyp::Identyfikator& identyfikatorPlanety)const{
		STyp::Wartosc rezultat = nastepna_->policzWartosc(wartosc, poziom, identyfikatorPlanety);
		STyp::Wartosc suma = 0;
		for (auto element : listaZmian_){
			if (element)
				suma += element->policzWartosc(rezultat, poziom, identyfikatorPlanety);
		}
		return suma;
	}

	bool ZmianaAgregacja::RejestrujZmianaAgregacja(ZmianaFabryka &fabryka){
		fabryka_ = &fabryka;
		return fabryka.rejestracjaZmiany(identyfikator_, ZmianaAgregacja::TworzZmianaAgregacja);
	}

	std::string ZmianaAgregacja::napis() const{
		SLog::Logger str(NAZWAKLASY(ZmianaAgregacja));
		if (nastepna_)
			str.dodajPole(NAZWAPOLA(nastepna_), *nastepna_);
		for (auto element : listaZmian_){
			if (element)
				str.dodajPole(NAZWAPOLA(element), *element);
		}
		return str.napis();
	}
}
