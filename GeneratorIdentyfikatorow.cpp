#include "GeneratorIdentyfikatorow.h"
#include "NiepoprawneParametryFunkcji.h"
#include "Aplikacja.h"

namespace SpEx{
	STyp::Identyfikator GeneratorIdentyfikatorow::pobierzIdentyfikator(const std::string& napis){
		if (napis.empty())
			throw NiepoprawneParametryFunkcji(EXCEPTION_PLACE, SpEx::Aplikacja::pobierzInstancje().pobierzSladStosu(), STyp::Tekst(napis));
		int pozycja = -1;
		auto iterator = std::find(mapa_.begin(), mapa_.end(), [&napis, &pozycja](Kontener::const_iterator iter)->bool{ ++pozycja; return *iter == napis; });
		if (iterator != mapa_.end()){
			return pozycja;
		}
		mapa_.emplace_back(napis);
		return mapa_.size()-1;
	}

	std::string GeneratorIdentyfikatorow::pobierzNapis(const STyp::Identyfikator& identyfikator) const{
		if (identyfikator() < 0 || identyfikator >= mapa_.size())
			return std::string();
		else
			return mapa_.at(identyfikator());
	}
};
