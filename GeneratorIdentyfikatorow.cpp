#include "GeneratorIdentyfikatorow.h"
#include "NiepoprawneParametryFunkcji.h"
#include "Aplikacja.h"

namespace SpEx{
	STyp::Identyfikator GeneratorIdentyfikatorow::pobierzIdentyfikator(const std::string& napis){
		if (napis.empty())
			throw NiepoprawneParametryFunkcji(EXCEPTION_PLACE, SpEx::Aplikacja::pobierzInstancje().pobierzSladStosu(), STyp::Tekst(napis));
		int pozycja = -1;
		for (auto& element : mapa_){
			++pozycja;
			if (napis == element){
				return pozycja;
			}
		}
		mapa_.emplace_back(napis);
		return static_cast<int>(mapa_.size())-1;
	}

	std::string GeneratorIdentyfikatorow::pobierzNapis(const STyp::Identyfikator& identyfikator) const{
		if (identyfikator < 0 || identyfikator >= static_cast<int>(mapa_.size()))
			return std::string();
		else
			return mapa_.at(identyfikator());
	}
};
