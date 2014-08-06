#include "GeneratorIdentyfikatorow.h"
#include "NiepoprawneParametryFunkcji.h"
#include "Aplikacja.h"

namespace SpEx{
	bool GeneratorIdentyfikatorow::pobierzIdentyfikator(const std::string& napis, STyp::Identyfikator& id){
		if (napis.empty())
			throw NiepoprawneParametryFunkcji(EXCEPTION_PLACE, SpEx::Aplikacja::pobierzInstancje().pobierzSladStosu(), STyp::Tekst(napis));
		int pozycja = -1;
		for (auto& element : mapa_){
			++pozycja;
			if (napis == element){
				id(pozycja);
				return false;
			}
		}
		mapa_.emplace_back(napis);
		id(static_cast<int>(mapa_.size()) - 1);
		return true;
	}

	std::string GeneratorIdentyfikatorow::pobierzNapis(const STyp::Identyfikator& identyfikator) const{
		if (identyfikator < 0 || identyfikator >= static_cast<int>(mapa_.size()))
			return std::string();
		else
			return mapa_.at(identyfikator());
	}
};
