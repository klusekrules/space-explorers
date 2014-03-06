#include "ZmianaPoziomObiektu.h"
#include "Aplikacja.h"
#include "Zmiana\ZmianaStaleXml.h"

namespace SpEx{

	ZmianaPoziomObiektu::ZmianaPoziomObiektu(XmlBO::ElementWezla e)
		: parametr_(XmlBO::ZnajdzWezel<THROW>(e, XML_WEZEL_ZMIANA_PARAM))
	{
	}

	STyp::Wartosc ZmianaPoziomObiektu::policzWartosc(const STyp::Wartosc& wartosc, const STyp::Poziom& poziom, const STyp::Identyfikator& identyfikatorPlanety) const{
		auto obiekt = Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(identyfikatorPlanety)->pobierzPoziomObiektu(parametr_.pobierzIdentyfikatorObiektu());
		return STyp::Wartosc(obiekt());
	}

	ZmianaPoziomObiektu* ZmianaPoziomObiektu::Kopia()const{
		return new ZmianaPoziomObiektu(*this);
	}

	bool ZmianaPoziomObiektu::RejestrujZmianaPoziomObiektu(SZmi::ZmianaFabryka &ref){
		return ref.rejestracjaZmiany(identyfikator_, ZmianaPoziomObiektu::TworzZmianaPoziomObiektu);
	}

	std::string ZmianaPoziomObiektu::napis()const{
		SLog::Logger str(NAZWAKLASY(ZmianaPoziomObiektu));
		str.dodajPole(NAZWAPOLA(parametr_), parametr_);
		return str.napis();
	}

	SZmi::ZmianaInterfejs* ZmianaPoziomObiektu::TworzZmianaPoziomObiektu(XmlBO::ElementWezla wezel){
		return new ZmianaPoziomObiektu(wezel);
	}

	const STyp::Identyfikator ZmianaPoziomObiektu::identyfikator_(6);

	bool RejestrujZmianaPoziomObiektu(SZmi::ZmianaFabryka& fabryka, SLog::Log& logger){
		if (ZmianaPoziomObiektu::RejestrujZmianaPoziomObiektu(fabryka))
			logger.loguj(SLog::Log::Info, "Zaladowano ZmianaPoziomObiektu."); //TODO: przeniesc do sta³ej.
		else
			logger.loguj(SLog::Log::Info, "Nie zaladowano ZmianaPoziomObiektu."); //TODO: przeniesc do sta³ej.
		return true;
	}
}
