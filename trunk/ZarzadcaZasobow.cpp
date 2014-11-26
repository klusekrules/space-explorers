#include "ZarzadcaZasobow.h"
#include "Utils.h"
#include "Aplikacja.h"
#include "definicjeWezlowXML.h"
#include "Logger\Logger.h"
#include "Parser\ParserDokumentXml.h"
#include "NieznalezionoPliku.h"

#define TYTUL_BLAD_WEZLA_ROOT STyp::Tekst("Nie uda�o si� pobra� elementu parsera!")
#define KOMUNIKAT_BLAD_WEZLA_ROOT( a ) STyp::Tekst("Podczas pr�by dost�pu do g��wnego w�z�a wyst�pi� b��d. Dokument wczytany z pliku: " + a)

#define TYTUL_BLAD_ATRYBUTU STyp::Tekst("Niepoprawna struktura elementu!")
#define KOMUNIKAT_BLAD_ATRYBUTU( a , b ) STyp::Tekst("Podczas pr�by odczytania danych wyst�pi�a niesp�jno�� w elemencie: " + a + ". Dokument wczytany z pliku: " + b)

#define TYTUL_BLAD_MAPOWANIA STyp::Tekst("Element istnieje!")
#define KOMUNIKAT_BLAD_MAPOWANIA( a , b , c , d ) STyp::Tekst("Nazwa: " + a + " posiada ju� przypisane id: " + b + ". W�ze�: " + c + ". Dokument wczytany z pliku: " + d)

#define TYTUL_BLAD_UNIKALNEGO_ZASOBU STyp::Tekst("B��d tworzenia unikalnego zasobu!")
#define KOMUNIKAT_BLAD_UNIKALNEGO_ZASOBU( a , b ) STyp::Tekst("Pr�ba wczytania typu, kt�ry nie jest obs�ugiwany. Typ: [" + a + "]. Parametr: " + b )

#define TYTUL_BLAD_ZASOBU STyp::Tekst("B��d tworzenia zasobu!")
#define KOMUNIKAT_BLAD_ZASOBU( a , b ) STyp::Tekst("Pr�ba wczytania typu, kt�ry nie jest obs�ugiwany. Typ: [" + a + "]. Parametr: " + b )

namespace SpEx{

	bool ZarzadcaZasobow::inicjalizuj(const UstawieniaAplikacji& ustawienia, const std::function<std::string()>& stos){
		
		auto plik = ustawienia.pobierzAdresPlikuPowiazanZasobow();
		auto dokument = std::make_shared<SPar::ParserDokumentXml>();
		if (!dokument->odczytaj(plik.c_str())){
			throw NieznalezionoPliku(EXCEPTION_PLACE, stos(), Utils::pobierzDebugInfo(), plik);
		}

		auto wezel = dokument->pobierzElement(nullptr);

		if (!wezel){
			throw STyp::Wyjatek(EXCEPTION_PLACE, stos(), Utils::pobierzDebugInfo(), STyp::Identyfikator(-1), TYTUL_BLAD_WEZLA_ROOT, KOMUNIKAT_BLAD_WEZLA_ROOT(plik));
		}

		resetuj();

		return XmlBO::ForEach<STACKTHROW>(wezel, WEZEL_XML_LOKALIZACJA_ZASOBU, XmlBO::OperacjaWezla([&](XmlBO::ElementWezla wpis)->bool{
			std::string nazwa;
			std::string lokalizacja;

			nazwa = XmlBO::WczytajAtrybut(wpis, ATRYBUT_XML_NAZWA, std::string());
			lokalizacja = XmlBO::WczytajAtrybut(wpis, ATRYBUT_XML_LOKALIZACJA, std::string());

			if (nazwa.empty() || lokalizacja.empty()){
				throw STyp::Wyjatek(EXCEPTION_PLACE, stos(), Utils::pobierzDebugInfo(), STyp::Identyfikator(-1), TYTUL_BLAD_ATRYBUTU,
					KOMUNIKAT_BLAD_ATRYBUTU(wpis->error(), ustawienia.pobierzAdresPlikuPowiazanZasobow()));
			}

			lokalizacjeZasobow_.push_back(std::make_pair(nazwa, lokalizacja));
			STyp::Identyfikator id;

			if (!mapujIdentyfikator(nazwa, id)){
				throw STyp::Wyjatek(EXCEPTION_PLACE, stos(), Utils::pobierzDebugInfo(), STyp::Identyfikator(-1), TYTUL_BLAD_MAPOWANIA,
					KOMUNIKAT_BLAD_MAPOWANIA(nazwa, id.napis(), wpis->error(), ustawienia.pobierzAdresPlikuPowiazanZasobow()));

			}
			return true;
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

	Zasob::SharedPtr ZarzadcaZasobow::pobierzZasob(const Parametr& parametr, bool cache, Identyfikator& id){
		return pobierzZasob(parametr, parametr, cache, id);
	}

	Zasob::SharedPtr ZarzadcaZasobow::pobierzZasob(const std::string& nazwa, const Parametr& parametr, bool cache, Identyfikator& id){
		STyp::Identyfikator identyfikator;
		mapujIdentyfikator(nazwa, identyfikator);
		STyp::Identyfikator lokalizator = pobierzIdentyfikator(parametr);
		if (lokalizator() != -1){
			return pobierzZasob(identyfikator, pobierzAdresObrazka(lokalizator), cache, id);
		}
		return pobierzZasob(identyfikator, parametr, cache, id);
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
			throw STyp::Wyjatek(EXCEPTION_PLACE, Aplikacja::pobierzInstancje().pobierzSladStosu(), Utils::pobierzDebugInfo(), STyp::Identyfikator(-1),
				TYTUL_BLAD_UNIKALNEGO_ZASOBU, KOMUNIKAT_BLAD_UNIKALNEGO_ZASOBU(typ, parametr));
		}
		return nullptr;
	}

	Zasob::SharedPtr ZarzadcaZasobow::pobierzZasob(const Identyfikator& identyfikator, const Parametr& parametr, bool cache, Identyfikator& id){
		auto found = zasobyPrzechowywane_.find(identyfikator);

		if (found != zasobyPrzechowywane_.end()){
			if (found->second.cached_){
				return found->second.sharedptr_;
			}else{
				Zasob::WeakPtr asset = found->second.weakptr_;

				if (!asset.expired()){
					return asset.lock();
				}else{
					zasobyPrzechowywane_.erase(found);
					return wczytajZasob(identyfikator, parametr, cache, id);
				}
			}
		}else{
			return wczytajZasob(identyfikator, parametr, cache, id);
		}
	}

	bool ZarzadcaZasobow::przechowywanyZasob(const Identyfikator& identyfikator) const{
		auto iter = zasobyPrzechowywane_.find(identyfikator);
		return iter != zasobyPrzechowywane_.end() ? iter->second.cached_ : false;
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

	Zasob::SharedPtr ZarzadcaZasobow::wczytajZasob(const Identyfikator& identyfikator, const Parametr& parametr, bool cache, Identyfikator& id ){
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
				zasobyPrzechowywane_[identyfikator] = WpisZasobu({asset, asset, cache, parametr});
			}else{
				zasobyPrzechowywane_[identyfikator] = WpisZasobu({asset, nullptr, cache, parametr});
			}
			if (!asset->inicjalizuj()){
				zasobyPrzechowywane_.erase(identyfikator);
				return nullptr;
			}
			id = identyfikator;
			return asset;
		}else{
			throw STyp::Wyjatek(EXCEPTION_PLACE, Aplikacja::pobierzInstancje().pobierzSladStosu(), Utils::pobierzDebugInfo(), STyp::Identyfikator(-1),
				TYTUL_BLAD_ZASOBU, KOMUNIKAT_BLAD_ZASOBU(typ, parametr));
		}
		return nullptr;
	}

	bool ZarzadcaZasobow::mapujIdentyfikator(const Parametr& parametr, STyp::Identyfikator& identyfikator){
		return generator_.pobierzIdentyfikator(parametr, identyfikator);
	}

	std::string ZarzadcaZasobow::napis() const{
		SLog::Logger logger(NAZWAKLASY(ZarzadcaZasobow));

		logger.rozpocznijPodKlase("SpEx::ZarzadcaZasobow::MapaInicjalizatorow");
		for (auto &element : inicjalizatory_){
			logger.rozpocznijPodKlase("Element");
			logger.dodajPole("Typ", NAZWAKLASY2(element.first), element.first);
			std::stringstream streamValid;
			streamValid.imbue(std::locale());
			streamValid << std::boolalpha << element.second.operator bool();
			logger.dodajPole("Poprawny", "bool", streamValid.str());
			logger.zakonczPodKlase();
		}
		logger.zakonczPodKlase();


		logger.rozpocznijPodKlase("SpEx::ZarzadcaZasobow::TablicaLokalizacjiZasobu");
		for (size_t i = 0; i < lokalizacjeZasobow_.size(); ++i){
			logger.rozpocznijPodKlase("SpEx::ZarzadcaZasobow::WpisLokalizacjiZasobu");
			auto &element = lokalizacjeZasobow_[i];
			//logger.dodajPole("IdentyfikatorWpisu", std::to_string(i));
			logger.dodajPole("IdentyfikatorZasobu", NAZWAKLASY2(element.first), element.first);
			logger.dodajPole("Lokalizacja", NAZWAKLASY2(element.second), element.second);
			logger.zakonczPodKlase();
		}
		logger.zakonczPodKlase();

		logger.dodajPole(NAZWAPOLA(generator_), generator_);

		logger.rozpocznijPodKlase("SpEx::ZarzadcaZasobow::MapaZasobow");
		for (auto &element : zasobyPrzechowywane_){

			logger.rozpocznijPodKlase("Element");
			logger.dodajPole("Identyfikator", element.first);
			logger.rozpocznijPodKlase("SpEx::ZarzadcaZasobow::WpisZasobu");

			std::stringstream streamWeakPtr;
			streamWeakPtr.imbue(std::locale("C"));
			streamWeakPtr << "0x" << std::hex << (unsigned int)(element.second.weakptr_._Get());
			logger.dodajPole("weakptr_", NAZWAKLASY2(element.second.weakptr_), streamWeakPtr.str());
			
			std::stringstream streamSharedPtr;
			streamSharedPtr.imbue(std::locale("C"));
			streamSharedPtr << "0x" << std::hex << (unsigned int)(element.second.sharedptr_._Get());
			logger.dodajPole("sharedptr_", NAZWAKLASY2(element.second.sharedptr_), streamSharedPtr.str());

			std::stringstream streamCached;
			streamCached.imbue(std::locale("C"));
			streamCached << std::boolalpha << element.second.cached_;
			logger.dodajPole("cached_", NAZWAKLASY2(element.second.cached_), streamCached.str());

			logger.dodajPole("parametr_", NAZWAKLASY2(element.second.parametr_), element.second.parametr_);

			logger.zakonczPodKlase();
			logger.zakonczPodKlase();
		}
		logger.zakonczPodKlase();

		logger.dodajPole(NAZWAPOLA(pustyNapis_), NAZWAKLASY2(pustyNapis_), pustyNapis_);

		return logger.napis();
	}
	
	void ZarzadcaZasobow::resetuj(){
		generator_.resetuj();
		lokalizacjeZasobow_.clear();
		zasobyPrzechowywane_.clear();
		inicjalizatory_.clear();
	}
};
