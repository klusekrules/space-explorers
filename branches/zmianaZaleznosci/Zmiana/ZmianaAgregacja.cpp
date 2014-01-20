#include "ZmianaAgregacja.h"
#include "ZmianaUtils.h"
#include "Logger\Logger.h"

namespace SZmi{
	ZmianaAgregacja::ZmianaAgregacja(XmlBO::ElementWezla wezel)
	{
		if (wezel && fabryka_){
			XmlBO::ElementWezla wezelNastepny = XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel, "Zmiana", "for", "nastepny"); //TODO: U¿yæ sta³ej.
			if (!wezelNastepny)
				ZmianaUtils::generujWyjatekBleduStruktury(wezel);
			nastepna_ = fabryka_->Tworz(wezelNastepny);
			if (!nastepna_)
				ZmianaUtils::generujWyjatekBleduStruktury(wezelNastepny);

			XmlBO::ElementWezla dziecko = XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel, "Zmiana", "for", "brat"); //TODO: U¿yæ sta³ej.
			if (!dziecko)
				ZmianaUtils::generujWyjatekBleduStruktury(wezel);
			for (; dziecko; dziecko = XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel, "Zmiana", "for", "brat", dziecko)){ //TODO: U¿yæ sta³ej.
				auto element = fabryka_->Tworz(dziecko);
				if (element)
					listaZmian_.push_back(element);
				else
					ZmianaUtils::generujWyjatekBleduStruktury(dziecko);
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

	long double ZmianaAgregacja::policzWartosc(long double wartosc, int poziom, int identyfikatorPlanety)const{
		long double rezultat = nastepna_->policzWartosc(wartosc, poziom, identyfikatorPlanety);
		long double suma = 0;
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
			str.dodajPole("Nastêpna", *nastepna_);
		for (auto element : listaZmian_){
			if (element)
				str.dodajPole("Brat", *element);
		}
		return str.napis();
	}
}
