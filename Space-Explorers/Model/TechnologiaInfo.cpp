#include "TechnologiaInfo.h"
#include "Logger\Logger.h"
#include "Kontroler\Gra.h"
#include "Planeta.h"

namespace SpEx{
	TechnologiaInfo::TechnologiaInfo(XmlBO::ElementWezla wezel)
		: ObiektInfo(TECHNOLOGIA, typAtrybutu, wezel)
	{
	}
	
	Technologia* TechnologiaInfo::tworzEgzemplarz(const PodstawoweParametry& parametry ) const{
		return new Technologia(parametry, *this);
	}
	
	bool TechnologiaInfo::tworz(Planeta& planeta, const PodstawoweParametry::AtrybutPodstawowy& atrybut) const{
		return planeta.dodajObiekt<Technologia>(Technologia::SharedPtr(tworzEgzemplarz(PodstawoweParametry(atrybut, typAtrybutu_))));
	}

	bool TechnologiaInfo::tworz(Planeta& planeta, const XmlBO::ElementWezla& element) const{
		auto technologia = Technologia::SharedPtr(tworzEgzemplarz(PodstawoweParametry(PodstawoweParametry::AtrybutPodstawowy(), typAtrybutu_)));
		if (technologia && element){
			if (!technologia->odczytaj(element))
				return false;
			return planeta.dodajObiekt<Technologia>(technologia);
		}
		return false;
	}

	std::string TechnologiaInfo::napis()const{
		SLog::Logger str(NAZWAKLASY(TechnologiaInfo));
		str.dodajKlase(ObiektInfo::napis());
		return str.napis();
	}
}