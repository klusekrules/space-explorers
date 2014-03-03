#include "TechnologiaInfo.h"
#include "Logger\Logger.h"
#include "Gra.h"

namespace SpEx{
	TechnologiaInfo::TechnologiaInfo(XmlBO::ElementWezla wezel)
		: ObiektInfo(wezel)
	{
	}
	
	Technologia* TechnologiaInfo::tworzEgzemplarz(const PodstawoweParametry& parametry ) const{
		return new Technologia(parametry, *this);
	}
	
	bool TechnologiaInfo::tworz(Planeta& planeta, const PodstawoweParametry::AtrybutPodstawowy atrybut) const{
		return planeta.dodajObiekt(std::shared_ptr<Technologia>(tworzEgzemplarz(PodstawoweParametry(atrybut, PodstawoweParametry::POZIOM))));
	}

	std::string TechnologiaInfo::napis()const{
		SLog::Logger str(NAZWAKLASY(TechnologiaInfo));
		str.dodajKlase(ObiektInfo::napis());
		return str.napis();
	}
}