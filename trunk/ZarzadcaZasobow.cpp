#include "ZarzadcaZasobow.h"
#include "Utils.h"

namespace SpEx{

	Zasob::SharedPtr ZarzadcaZasobow::pobierzZasob(const Parametr& parametr, bool cache){
		STyp::Identyfikator identyfikator;
		mapujIdentyfikator(parametr, identyfikator);
		return pobierzZasob(identyfikator, parametr, cache);
	}

	Zasob::SharedPtr ZarzadcaZasobow::pobierzUnikalnyZasob(const Parametr& parametr){
		std::string typ;
		if (!Utils::pobierzRozszezenie(parametr, typ))
			return nullptr;
		auto found = inicjalizatory_.find(typ);
		if (found != inicjalizatory_.end()){
			Zasob::SharedPtr asset = found->second(parametr, false);
			if(!asset->inicjalizuj())
				return nullptr;
			return asset;
		}else{
			throw std::exception("unsupported asset extension detected");
		}
		return nullptr;
	}

	Zasob::SharedPtr ZarzadcaZasobow::pobierzZasob(const Identyfikator& identyfikator, const Parametr& parametr, bool cache){
		auto found = zasobyPrzechowywane_.find(identyfikator);

		if (found != zasobyPrzechowywane_.end()){
			if (found->second.second){
				return found->second.first.second;
			}else{
				Zasob::WeakPtr asset = found->second.first.first;

				if (!asset.expired()){
					return asset.lock();
				}else{
					return wczytajZasob(identyfikator, parametr, cache);
				}
			}
		}else{
			return wczytajZasob(identyfikator, parametr, cache);
		}
	}

	bool ZarzadcaZasobow::przechowywanyZasob(const Identyfikator& identyfikator) const{
		auto iter = zasobyPrzechowywane_.find(identyfikator);
		return iter != zasobyPrzechowywane_.end() ? iter->second.second : false;
	}

	bool ZarzadcaZasobow::rejestrujInicjalizator(const std::string& typ, Inicjalizator funkcja){
		auto found = inicjalizatory_.find(typ);
		if (found == inicjalizatory_.end()){
			inicjalizatory_.emplace(typ, funkcja);
			return true;
		}
		return false;
	}

	bool ZarzadcaZasobow::dostepnyInicjalizator(const std::string& typ) const{
		return inicjalizatory_.find(typ) != inicjalizatory_.end();
	}

	bool ZarzadcaZasobow::zwolnijZasobPrzechowywany(const Identyfikator& identyfikator){
		auto found = zasobyPrzechowywane_.find(identyfikator);
		if (found != zasobyPrzechowywane_.end()){
			zasobyPrzechowywane_.erase(found);
			return true;
		}
		return false;
	}

	ZarzadcaZasobow::Inicjalizator ZarzadcaZasobow::wyrejestrujInicjalizator(const std::string& typ){
		auto found = inicjalizatory_.find(typ);
		if (found != inicjalizatory_.end()){
			Inicjalizator loader = found->second;
			inicjalizatory_.erase(found);
			return loader;
		}
		return nullptr;
	}

	Zasob::SharedPtr ZarzadcaZasobow::wczytajZasob(const Identyfikator& identyfikator, const Parametr& parametr, bool cache){
		if (zasobyPrzechowywane_.find(identyfikator) != zasobyPrzechowywane_.end()){
			return nullptr;
		}
		std::string typ;
		if (!Utils::pobierzRozszezenie(parametr, typ))
			return nullptr;

		auto found = inicjalizatory_.find(typ);
		if (found != inicjalizatory_.end()){
			Zasob::SharedPtr asset = found->second(parametr, cache);
			asset->identyfikator_ = identyfikator;
			if (cache){
				zasobyPrzechowywane_[identyfikator] = std::make_pair(std::make_pair(asset, asset), cache);
			}else{
				zasobyPrzechowywane_[identyfikator] = std::make_pair(std::make_pair(asset, nullptr), cache);
			}
			if (!asset->inicjalizuj()){
				return nullptr;
			}
			return asset;
		}else{
			throw std::exception("unsupported asset extension detected");
		}
		return nullptr;
	}

	bool ZarzadcaZasobow::mapujIdentyfikator(const Parametr& parametr, STyp::Identyfikator& identyfikator){
		return generator_.pobierzIdentyfikator(parametr, identyfikator);
	}
};
