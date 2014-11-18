#include "ZarzadcaZasobow.h"
#include "Utils.h"
#include "definicjeWezlowXML.h"
#include "Logger\Logger.h"

namespace SpEx{

	bool ZarzadcaZasobow::inicjalizuj(XmlBO::ElementWezla wezel){
		if (!wezel)
			return false;
		return XmlBO::ForEach<STACKTHROW>(wezel, WEZEL_XML_LOKALIZACJA_ZASOBU, XmlBO::OperacjaWezla([&](XmlBO::ElementWezla wpis)->bool{
			std::string nazwa;
			std::string lokalizacja;

			nazwa = XmlBO::WczytajAtrybut(wpis, ATRYBUT_XML_NAZWA, std::string());
			lokalizacja = XmlBO::WczytajAtrybut(wpis, ATRYBUT_XML_LOKALIZACJA, std::string());

			if (nazwa.empty() || lokalizacja.empty())
				return false;
			lokalizacjeZasobow_.push_back(std::make_pair(nazwa, lokalizacja));
			return mapujIdentyfikator(nazwa, STyp::Identyfikator());
		}));
	}
	
	STyp::Identyfikator ZarzadcaZasobow::pobierzIdentyfikator(const Parametr& nazwaObrazka) const{
		for (unsigned int n = 0; n < lokalizacjeZasobow_.size(); ++n){
			if (lokalizacjeZasobow_[n].first == nazwaObrazka)
				return n;
		}
		return -1; // Niepoprawny identyfikator.
	}

	const std::string& ZarzadcaZasobow::pobierzAdresObrazka(const STyp::Identyfikator& identyfikator) const{
		if (static_cast<STyp::SPG::Identyfikator>(lokalizacjeZasobow_.size()) <= identyfikator() || identyfikator() < 0)
			return pustyNapis_;
		return lokalizacjeZasobow_[identyfikator()].second;
	}

	ZarzadcaZasobow::Identyfikator ZarzadcaZasobow::pobierzKlucz(const Parametr& identyfikator){
		STyp::Identyfikator id;
		mapujIdentyfikator(identyfikator, id);
		return id;
	}

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

	std::string ZarzadcaZasobow::napis() const{
		SLog::Logger logger(NAZWAKLASY(ZarzadcaZasobow));

		logger.rozpocznijPodKlase(NAZWAPOLA(MapaInicjalizatorow));
		for (auto &element : inicjalizatory_){
			logger.rozpocznijPodKlase("Inicjalizator");
			logger.dodajPole("Typ", NAZWAKLASY2(element.first), element.first);
			std::stringstream streamValid;
			streamValid.imbue(std::locale());
			streamValid << std::boolalpha << element.second.operator bool();
			logger.dodajPole("Poprawny", "bool", streamValid.str());
			logger.zakonczPodKlase();
		}
		logger.zakonczPodKlase();


		logger.rozpocznijPodKlase(NAZWAPOLA(TablicaLokalizacjiZasobu));
		for (size_t i = 0; i < lokalizacjeZasobow_.size(); ++i){
			logger.rozpocznijPodKlase(NAZWAPOLA(WpisLokalizacjiZasobu));
			auto &element = lokalizacjeZasobow_[i];
			//logger.dodajPole("IdentyfikatorWpisu", std::to_string(i));
			logger.dodajPole("IdentyfikatorZasobu", NAZWAKLASY2(element.first), element.first);
			logger.dodajPole("Lokalizacja", NAZWAKLASY2(element.second), element.second);
			logger.zakonczPodKlase();
		}
		logger.zakonczPodKlase();

		logger.dodajPole(NAZWAPOLA(generator_), generator_);

		logger.rozpocznijPodKlase(NAZWAPOLA(MapaZasobow));
		for (auto &element : zasobyPrzechowywane_){

			logger.rozpocznijPodKlase("Element");
			logger.dodajPole("Identyfikator", element.first);
			logger.rozpocznijPodKlase(NAZWAPOLA(WpisZasobu));

			std::stringstream streamWeakPtr;
			streamWeakPtr.imbue(std::locale("C"));
			streamWeakPtr << "0x" << std::hex << (unsigned int)(element.second.first.first._Get());
			logger.dodajPole("SlabyWsk", NAZWAKLASY2(element.second.first.first), streamWeakPtr.str());
			
			std::stringstream streamSharedPtr;
			streamSharedPtr.imbue(std::locale("C"));
			streamSharedPtr << "0x" << std::hex << (unsigned int)(element.second.first.second._Get());
			logger.dodajPole("SilnyWsk", NAZWAKLASY2(element.second.first.second), streamSharedPtr.str());

			std::stringstream streamCached;
			streamCached.imbue(std::locale("C"));
			streamCached << std::boolalpha << element.second.second;
			logger.dodajPole("Przechowywany", NAZWAKLASY2(element.second.second), streamCached.str());

			logger.zakonczPodKlase();
			logger.zakonczPodKlase();
		}
		logger.zakonczPodKlase();

		logger.dodajPole(NAZWAPOLA(pustyNapis_), NAZWAKLASY2(pustyNapis_), pustyNapis_);

		return logger.napis();
	}
};
