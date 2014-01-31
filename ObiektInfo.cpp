#include "ObiektInfo.h"
#include "Aplikacja.h"
#include "definicjeWezlowXML.h"
#include "Logger\Logger.h"

namespace SpEx{

	ObiektInfo::ObiektInfo(XmlBO::ElementWezla wezel)
		: Info(wezel), Wymagania(wezel)
	{
	}

	/*Obiekt* ObiektInfo::tworzEgzemplarz(const PodstawoweParametry& parametry) const {
		return new Obiekt(ilosc, pobierzPoziom(), identyfikatorPlanety, *this);
	}*/

	/*bool ObiektBazowyInfo::tworz(Planeta& planeta, const PodstawoweParametry::AtrybutPodstawowy atrybut) const{
		return false;
	}*/

	std::string ObiektInfo::napis() const{
		SLog::Logger str(NAZWAKLASY(ObiektInfo));
		str.dodajKlase(Info::napis());
		str.dodajKlase(Wymagania::napis());
		return str.napis();
	}
}
