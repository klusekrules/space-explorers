#include "GeneratorIdentyfikatorow.h"
#include "Logger\Logger.h"

namespace SpEx{
	
	bool GeneratorIdentyfikatorow::pobierzIdentyfikator(const std::string& napis, STyp::Identyfikator& id){
		if (napis.empty())
			throw std::exception("GeneratorIdentyfikatorow::pobierzIdentyfikator -> Brak nazwy identyfikatora.");

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

	std::string GeneratorIdentyfikatorow::napis() const{
		SLog::Logger logger(NAZWAKLASY(GeneratorIdentyfikatorow));
		for (size_t i = 0; i < mapa_.size(); ++i){
			logger.dodajPole(NAZWAPOLA(mapa_) + std::to_string(i), NAZWAKLASY2(mapa_[i]), mapa_[i]);
		}
		return logger.napis();
	}

	void GeneratorIdentyfikatorow::resetuj(){
		mapa_.clear();
	}
};
