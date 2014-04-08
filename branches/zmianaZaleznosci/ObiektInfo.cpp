#include "ObiektInfo.h"
#include "Aplikacja.h"
#include "definicjeWezlowXML.h"
#include "Logger\Logger.h"

namespace SpEx{

	ObiektInfo::ObiektInfo(const STyp::Identyfikator& typ, XmlBO::ElementWezla wezel)
		: Info(typ, wezel), Wymagania(wezel)
	{
	}

	std::string ObiektInfo::napis() const{
		SLog::Logger str(NAZWAKLASY(ObiektInfo));
		str.dodajKlase(Info::napis());
		str.dodajKlase(Wymagania::napis());
		return str.napis();
	}
}
