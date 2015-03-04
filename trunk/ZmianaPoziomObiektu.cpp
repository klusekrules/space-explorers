#include "ZmianaPoziomObiektu.h"
#include "Aplikacja.h"
#include "Logger\Logger.h"
#include "StackThrow.h"
#include "Gra.h"
#include "Zmiana\ZmianaStaleXml.h"
#include "Planeta.h"

namespace SpEx{

	ZmianaPoziomObiektu::ZmianaPoziomObiektu(XmlBO::ElementWezla e)
		: parametr_(XmlBO::ZnajdzWezel<STACKTHROW>(e, XML_WEZEL_ZMIANA_PARAM))
	{
	}

	STyp::Wartosc ZmianaPoziomObiektu::policzWartosc(const STyp::Wartosc& wartosc, const STyp::Poziom& poziom, const STyp::Identyfikator& identyfikatorPlanety) const{
		auto ptr = Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(identyfikatorPlanety);
		if (ptr){
			auto obiekt = ptr->pobierzPoziomObiektu(parametr_.pobierzIdentyfikatorObiektu());
			return STyp::Wartosc(obiekt());
		}
		return 0;
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
		return ZmianaPoziomObiektu::RejestrujZmianaPoziomObiektu(fabryka);
	}
}
