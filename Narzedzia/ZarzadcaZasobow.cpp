#include "ZarzadcaZasobow.h"
#include "Logger\Logger.h"
#include "Parser\ParserDokumentXml.h"
#include "LuaState.h"
#include "DllModule.h"
#include "XmlModul.h"
#include "SumaKontrolnaPliku.h"
#include "Stale.h"

#define WEZEL_XML_LOKALIZACJA_ZASOBU "LokalizacjaZasobu"
#define ATRYBUT_XML_LOKALIZACJA "lokalizacja"
#define ATRYBUT_XML_NAZWA "nazwa"

#define TYTUL_BLAD_OTWIERANIA_PLIKU STyp::Tekst("Nie uda³o siê otworzyæ pliku!")
#define KOMUNIKAT_BLAD_OTWIERANIA_PLIKU( a ) STyp::Tekst("Podczas próby otwierania pliku: " + a + " wyst¹pi³ b³¹d!")

#define TYTUL_BLAD_WEZLA_ROOT STyp::Tekst("Nie uda³o siê pobraæ elementu parsera!")
#define KOMUNIKAT_BLAD_WEZLA_ROOT( a ) STyp::Tekst("Podczas próby dostêpu do g³ównego wêz³a wyst¹pi³ b³¹d. Dokument wczytany z pliku: " + a)

#define TYTUL_BLAD_ATRYBUTU STyp::Tekst("Niepoprawna struktura elementu!")
#define KOMUNIKAT_BLAD_ATRYBUTU( a , b ) STyp::Tekst("Podczas próby odczytania danych wyst¹pi³a niespójnoœæ w elemencie: " + a + ". Dokument wczytany z pliku: " + b)

#define TYTUL_BLAD_MAPOWANIA STyp::Tekst("Element istnieje!")
#define KOMUNIKAT_BLAD_MAPOWANIA( a , b , c , d ) STyp::Tekst("Nazwa: " + a + " posiada ju¿ przypisane id: " + b + ". Wêze³: " + c + ". Dokument wczytany z pliku: " + d)

#define TYTUL_BLAD_UNIKALNEGO_ZASOBU STyp::Tekst("B³¹d tworzenia unikalnego zasobu!")
#define KOMUNIKAT_BLAD_UNIKALNEGO_ZASOBU( a ) STyp::Tekst("Próba wczytania typu, który nie jest obs³ugiwany. Parametr: " + a )

#define TYTUL_BLAD_ZASOBU STyp::Tekst("B³¹d tworzenia zasobu!")
#define KOMUNIKAT_BLAD_ZASOBU( a ) STyp::Tekst("Próba wczytania typu, który nie jest obs³ugiwany. Parametr: " + a )

namespace SpEx{

	bool ZarzadcaZasobow::inicjalizuj(const UstawieniaAplikacji& ustawienia){
		
		std::string plik;
		if(!ustawienia[ATRYBUT_GLOWNY_FOLDER_GRY].empty())
			plik += ustawienia[ATRYBUT_GLOWNY_FOLDER_GRY] + "\\";
		plik += ustawienia[ATRYBUT_POWIAZANIA_ZASOBOW];
		auto dokument = std::make_shared<SPar::ParserDokumentXml>();
		if (!dokument->odczytaj(plik.c_str())){
			throw STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(), STyp::Identyfikator(-1), TYTUL_BLAD_OTWIERANIA_PLIKU, KOMUNIKAT_BLAD_OTWIERANIA_PLIKU(plik));
		}

		auto wezel = dokument->pobierzElement(nullptr);

		if (!wezel){
			throw STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(), STyp::Identyfikator(-1), TYTUL_BLAD_WEZLA_ROOT, KOMUNIKAT_BLAD_WEZLA_ROOT(plik));
		}

		resetuj();

		return XmlBO::ForEach<THROW>(wezel, WEZEL_XML_LOKALIZACJA_ZASOBU, XmlBO::OperacjaWezla([&](XmlBO::ElementWezla wpis)->bool{
			std::string nazwa;
			std::string lokalizacja;

			nazwa = XmlBO::WczytajAtrybut(wpis, ATRYBUT_XML_NAZWA, std::string());
			lokalizacja = XmlBO::WczytajAtrybut(wpis, ATRYBUT_XML_LOKALIZACJA, std::string());

			if (nazwa.empty() || lokalizacja.empty()){
				throw STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(), STyp::Identyfikator(-1), TYTUL_BLAD_ATRYBUTU,
					KOMUNIKAT_BLAD_ATRYBUTU(wpis->error(), ustawienia[ATRYBUT_POWIAZANIA_ZASOBOW]));
			}

			lokalizacjeZasobow_.push_back(std::make_pair(nazwa, lokalizacja));
			STyp::Identyfikator id;

			if (!mapujIdentyfikator(nazwa, id)){
				throw STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(), STyp::Identyfikator(-1), TYTUL_BLAD_MAPOWANIA,
					KOMUNIKAT_BLAD_MAPOWANIA(nazwa, id.napis(), wpis->error(), ustawienia[ATRYBUT_POWIAZANIA_ZASOBOW]));

			}
			return true;
		}));
	}

	void ZarzadcaZasobow::rejestrujTypyWbudowane(){
		rejestruj<LuaState>();
		rejestruj<DllModule>();
		rejestruj<XmlModul>();
		rejestruj<SumaKontrolnaPliku>();
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

	bool ZarzadcaZasobow::dodajInicjalizator(const std::string& typ, Inicjalizator inicjalizator){
		auto found = inicjalizatory_.find(typ);
		if (found == inicjalizatory_.end()){
			inicjalizatory_.emplace(typ, inicjalizator);
			return true;
		}
		return false;
	}

	
	ZarzadcaZasobow::Inicjalizator ZarzadcaZasobow::pobierzInicjalizator(const std::string& typ){
		auto found = inicjalizatory_.find(typ);
		if (found != inicjalizatory_.end()){
			return found->second;
		}
		return nullptr;
	}

	Zasob::SharedPtr ZarzadcaZasobow::pobierzZasob(Inicjalizator inicjalizator, const std::string& nazwa, const Parametr& parametr, bool cache, Identyfikator& id){
		STyp::Identyfikator identyfikator;
		mapujIdentyfikator(nazwa, identyfikator);
		STyp::Identyfikator lokalizator = pobierzIdentyfikator(parametr);
		if (lokalizator() != -1){
			return pobierzZasob(inicjalizator, identyfikator, pobierzAdresObrazka(lokalizator), cache, id);
		}
		return pobierzZasob(inicjalizator, identyfikator, parametr, cache, id);
	}

	Zasob::SharedPtr ZarzadcaZasobow::pobierzUnikalnyZasob(Inicjalizator inicjalizator, const Parametr& parametr){
		if (inicjalizator!=nullptr){
			Zasob::SharedPtr asset = inicjalizator(parametr, false);
			if(!asset->inicjalizuj())
				return nullptr;
			return asset;
		}else{
			throw STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(), STyp::Identyfikator(-1),
				TYTUL_BLAD_UNIKALNEGO_ZASOBU, KOMUNIKAT_BLAD_UNIKALNEGO_ZASOBU(parametr));
		}
		return nullptr;
	}

	Zasob::SharedPtr ZarzadcaZasobow::pobierzZasob(Inicjalizator inicjalizator, const Identyfikator& identyfikator, const Parametr& parametr, bool cache, Identyfikator& id){
		auto found = zasobyPrzechowywane_.find(identyfikator);

		if (found != zasobyPrzechowywane_.end()){
			if (found->second.cached_){
				wywolaj(StrukturyZarzadcyZasobow::PobranoPrzechowywany, found->second.sharedptr_->nazwa(), found->second.sharedptr_);
				return found->second.sharedptr_;
			}else{
				Zasob::WeakPtr asset = found->second.weakptr_;

				if (!asset.expired()){
					Zasob::SharedPtr ptr = asset.lock();
					wywolaj(StrukturyZarzadcyZasobow::PobranoPrzechowywany, ptr->nazwa(), ptr);
					return ptr;
				}else{
					zasobyPrzechowywane_.erase(found);
					return wczytajZasob(inicjalizator, identyfikator, parametr, cache, id);
				}
			}
		}else{
			return wczytajZasob(inicjalizator, identyfikator, parametr, cache, id);
		}
	}

	bool ZarzadcaZasobow::przechowywanyZasob(const Identyfikator& identyfikator) const{
		auto iter = zasobyPrzechowywane_.find(identyfikator);
		return iter != zasobyPrzechowywane_.end() ? iter->second.cached_ : false;
	}

	bool ZarzadcaZasobow::zwolnijZasobPrzechowywany(const Identyfikator& identyfikator){
		auto found = zasobyPrzechowywane_.find(identyfikator);
		if (found != zasobyPrzechowywane_.end()){
			zasobyPrzechowywane_.erase(found);
			return true;
		}
		return false;
	}
	
	Zasob::SharedPtr ZarzadcaZasobow::wczytajZasob(Inicjalizator inicjalizator, const Identyfikator& identyfikator, const Parametr& parametr, bool cache, Identyfikator& id){
		if (zasobyPrzechowywane_.find(identyfikator) != zasobyPrzechowywane_.end()){
			return nullptr;
		}

		if (inicjalizator!=nullptr){
			Zasob::SharedPtr asset = inicjalizator(parametr, cache);
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
			throw STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(), STyp::Identyfikator(-1),
				TYTUL_BLAD_ZASOBU, KOMUNIKAT_BLAD_ZASOBU(parametr));
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

			std::stringstream streamSharedPtr;
			streamSharedPtr.imbue(std::locale("C"));
			streamSharedPtr << "0x" << std::hex << (unsigned __int64)(element.second.sharedptr_.get());
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
