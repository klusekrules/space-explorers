#include "OknoGry.h"
#include "Kontroler\MaszynaStanow\MaszynaStanow.h"
#include <SFML\OpenGL.hpp>
#include "EkranStartowy.h"
#include "Utils\DefinicjeWezlowXML.h"
#include "Kontroler\Aplikacja.h"
#include "Narzedzia\FPSCounter.h"
#include "Wyjatki\PowtorzenieIdObiektu.h"
#include "Narzedzia\XmlModul.h"
#include "Wyjatki\NieznalezionoPliku.h"
#include "Logger\Logger.h"
#include "Narzedzia\ZarzadcaZasobow.h"
#include "Utils\Utils.h"
#include "Utils\StackThrow.h"

#define KOMUNIKAT_POWTORZENIE_OBIEKTU(a) STyp::Tekst("Obiekt typu: "#a )
#define GL_SHADING_LANGUAGE_VERSION       0x8B8C
namespace SpEx{
	OknoGry::OknoGry(bool wstrzymany)
		: Watek(wstrzymany), oknoGlowne_(nullptr)
	{
		przetwarzanie_ = true;
		inicjalizacjaWynik_ = inicjalizacja_.get_future();
	}

	bool OknoGry::czekajNaInicjalizacje(){
		inicjalizacjaWynik_.wait();
		return inicjalizacjaWynik_.get();
	}

	void OknoGry::zatrzymajPoInicjalizacji(){
		mutexUruchom_.lock();
	}

	void OknoGry::uruchom(){
		mutexUruchom_.try_lock();
		mutexUruchom_.unlock();
	}

	OknoGry::StosEkranow& OknoGry::pobierzStosEkranow(){
		return stosEkranow_;
	}

	void OknoGry::wyswietlWiadomoscWGUI(unsigned int typ, const std::string& tresc){
		for (auto& ekran : stosEkranow_)
			if (ekran && ekran->dodajWiadomoscGui(typ, tresc))
				break;
	}

	OknoGry::EkranPtr OknoGry::pobierzEkran(const STyp::Identyfikator& ekranId){
		std::lock_guard<std::recursive_mutex> lock(mutexListaEkranow_);
		auto iter = listaEkranow_.find(ekranId);
		if (iter != listaEkranow_.end()){
			return iter->second;
		}
		return nullptr;
	}

	Stan::KrokCzasu OknoGry::obliczZmianeCzasu(std::chrono::high_resolution_clock::time_point punkt){
		static std::chrono::high_resolution_clock::time_point punktCzasu = std::chrono::high_resolution_clock::now();
		auto ret = punkt - punktCzasu;
		punktCzasu = punkt;
		return ret;
	}

	void OknoGry::dodajZadanie(SpEx::Zadanie& zadanie){
		std::lock_guard<std::mutex>lock(listaZadanMux_);
		listaZadan_.push_back(zadanie);
	}

	void OknoGry::pause(){
		mutexPauza_.lock();
		boolPauza_ = true;
	}

	bool OknoGry::isPause() const{
		return boolPauza_;
	}

	void OknoGry::unpause(){
		mutexPauza_.unlock();
	}

	void OknoGry::wykonuj(){
		if (!przetwarzanie_){
			inicjalizacja_.set_value(false);
			return;
		}
		try{
			try{
				if (!inicjalizacja()){
					inicjalizacja_.set_value(false);
#ifndef LOG_OFF_ALL
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d inicjalizacji.");
#endif
					return;
				}
			}
			catch (...){
				inicjalizacja_.set_value(false);
				throw;
			}
			std::lock_guard<std::mutex> blokada(mutexUruchom_);

			Stan::KrokCzasu accumulator;

			{
				auto zerowanie = std::chrono::high_resolution_clock::now();
				accumulator = zerowanie - zerowanie;
			}

			if(oknoGlowne_)
				oknoGlowne_->setVisible(true);
#ifdef _FPS_COUNT
			FPSCounter fpsCounter;
#endif
			while (przetwarzanie_)
			{
#ifdef _FPS_COUNT
				fpsCounter.nextFrame();
#endif
				Stan stan = MaszynaStanow::pobierzInstancje().pobierzStan(stosEkranow_);
				accumulator += obliczZmianeCzasu(std::chrono::high_resolution_clock::now());

				stan.dt_ = accumulator;

				obslugaZdarzen(stan);
				uaktualnianie(stan);

				accumulator = stan.dt_;

				odmaluj();

				do{
					if (!listaZadan_.empty()){
						std::lock_guard<std::mutex>lock(listaZadanMux_);
						for (auto zadanie : listaZadan_){
							zadanie.wykonaj();
						}
						listaZadan_.clear();
					}
					if (boolPauza_){
						if (mutexPauza_.try_lock()){
							boolPauza_ = false;
							mutexPauza_.unlock();
						}
						else{
							std::this_thread::yield();
						}
					}
				} while (boolPauza_);

#ifdef _FPS_COUNT	
				if (fpsCounter.ready())
				{
					Aplikacja::pobierzInstancje().pobierzLogger().loguj(SLog::Log::Error, std::string("OknoGry: ") + std::to_string(fpsCounter.FPS()));
				}
#endif
			}
		}
		catch (STyp::Wyjatek& e){
			ustawBlad(e);
			MaszynaStanow::pobierzInstancje().inicjujZamykanie();
		}
		catch (std::exception& e){
			ustawBlad(STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(), -1, STyp::Tekst("Przechwycono wyj¹tek!"), STyp::Tekst(e.what())));
			MaszynaStanow::pobierzInstancje().inicjujZamykanie();
		}
		catch (...){
			ustawBlad(STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(), -1, STyp::Tekst("Przechwycono wyj¹tek!"), STyp::Tekst("Nieznany typ wyj¹tku!")));
			MaszynaStanow::pobierzInstancje().inicjujZamykanie();
		}

		usunWszystkieEkrany();
		stosEkranow_.clear();
		listaZadan_.clear();
		if (oknoGlowne_)
			oknoGlowne_->close();
	}

	bool OknoGry::inicjalizacja(){
		std::lock_guard<std::mutex> blokada(mutexInicjalizacja_);
		przetwarzanie_ = false;
		logujInfo();
		oknoGlowne_ = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 500), "Space-Explorers" , sf::Style::None);
		oknoGlowne_->setVisible(false);
		oknoGlowne_->setVerticalSyncEnabled(true);
		
		SetWindowLong(oknoGlowne_->getSystemHandle(), GWL_EXSTYLE, GetWindowLong(oknoGlowne_->getSystemHandle(), GWL_EXSTYLE) | WS_EX_LAYERED);
		if (!SetLayeredWindowAttributes(oknoGlowne_->getSystemHandle(), NULL, 0, LWA_ALPHA)){
#ifndef LOG_OFF_ALL
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Nie dziala przezroczstosc.");
#endif
		}

		if (!wczytajEkrany()){
#ifndef LOG_OFF_ALL
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Nieuda³o siê wczytaæ ekranów.");
#endif
			return false;
		}

		inicjalizacja_.set_value(true);
		przetwarzanie_ = true;
		return true;
	}

	void OknoGry::logujInfo(){
		if (sf::Shader::isAvailable()){
#ifndef LOG_OFF_ALL
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Shadery dostepne");
#endif
		}
		else{
			MessageBox(
				nullptr,
				"Karta graficzna nie wspiera shaderów.",
				"Fatal error",
				MB_ICONERROR
				);
#ifndef LOG_OFF_ALL
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Shadery niedostepne");
#endif
		}
#ifndef LOG_OFF_ALL
		char* p = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
		if(p)
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, p);
		p = (char*)glGetString(GL_VERSION);
		if (p)
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, p);
		p = (char*)glGetString(GL_VENDOR);
		if (p)
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, p);
#endif
	}

	bool OknoGry::wczytajEkrany(){
		std::lock_guard<std::recursive_mutex> lock(mutexListaEkranow_);
		auto zasob = SpEx::Aplikacja::pobierzInstancje().pobierzZarzadceZasobow().pobierzZasob<XmlModul>("KonfiguracjaOknaGry");
		if (!zasob)
			throw NieznalezionoPliku(EXCEPTION_PLACE, Utils::pobierzDebugInfo(), STyp::Tekst("Nie udalo sie wczytac dokumentu xml: KonfiguracjaOknaGry"));
		auto wezel = (*zasob)()->pobierzElement(nullptr);
		if (wezel&& oknoGlowne_){
			XmlBO::ForEach<SpEx::STACKTHROW>(wezel, WEZEL_XML_EKRAN_STARTOWY, XmlBO::OperacjaWezla([&](XmlBO::ElementWezla element)->bool{
				auto ptr = std::make_shared<EkranStartowy>(*oknoGlowne_, element); 
				if (listaEkranow_.find(ptr->pobierzId()) != listaEkranow_.end())
					throw PowtorzenieIdObiektu(EXCEPTION_PLACE, Utils::pobierzDebugInfo(), ptr->pobierzId(), KOMUNIKAT_POWTORZENIE_OBIEKTU(EkranStartowy));
				listaEkranow_.insert(std::make_pair(ptr->pobierzId(), ptr));
				return true;
			}));

			XmlBO::ForEach<SpEx::STACKTHROW>(wezel, WEZEL_XML_EKRAN, XmlBO::OperacjaWezla([&](XmlBO::ElementWezla element)->bool{
				auto ptr = std::make_shared<EkranSzablon>(element);
				if (listaEkranow_.find(ptr->pobierzId()) != listaEkranow_.end())
					throw PowtorzenieIdObiektu(EXCEPTION_PLACE, Utils::pobierzDebugInfo(), ptr->pobierzId(), KOMUNIKAT_POWTORZENIE_OBIEKTU(EkranSzablon));
				ptr->podlacz(*oknoGlowne_);
				listaEkranow_.insert(std::make_pair(ptr->pobierzId(), ptr));
				return true;
			}));
		}
		return !listaEkranow_.empty();
	}
	
	void OknoGry::usunWszystkieEkrany(){
		if (oknoGlowne_) {
			for (auto ekran : listaEkranow_) {
				ekran.second->odlacz(*oknoGlowne_);
				ekran.second->clear();
			}
		}
		listaEkranow_.clear();
	}
	
	void OknoGry::przeladujEkran(const STyp::Identyfikator& id){
		std::lock_guard<std::recursive_mutex> lock(mutexListaEkranow_);
		auto iter = listaEkranow_.find(id);
		if (iter!= listaEkranow_.end()){
			auto zasob = SpEx::Aplikacja::pobierzInstancje().pobierzZarzadceZasobow().pobierzZasob<XmlModul>("KonfiguracjaOknaGry");
			if (!zasob)
				throw NieznalezionoPliku(EXCEPTION_PLACE, Utils::pobierzDebugInfo(), STyp::Tekst("Nie udalo sie wczytac dokumentu xml: KonfiguracjaOknaGry"));
			auto wezel = (*zasob)()->pobierzElement(nullptr);
			auto okno = XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel, WEZEL_XML_EKRAN, ATRYBUT_XML_IDENTYFIKATOR, std::to_string(id()));
			if (okno && oknoGlowne_){
				auto ptr = std::make_shared<EkranSzablon>(okno);
				ptr->podlacz(*oknoGlowne_);
				iter->second = ptr;
			}
		}
	}
	
	void OknoGry::obslugaZdarzen(Stan& stan){
		sf::Event zdarzenie;
		if (oknoGlowne_) {
			while (oknoGlowne_->pollEvent(zdarzenie))
			{
				switch (zdarzenie.type) {
				case sf::Event::Closed:
					MaszynaStanow::pobierzInstancje().inicjujZamykanie();
					break;
				case sf::Event::MouseButtonPressed:
					SetActiveWindow(oknoGlowne_->getSystemHandle());
					break;
				case sf::Event::Resized:
				{
					sf::FloatRect visibleArea(0, 0, static_cast<float>(zdarzenie.size.width), static_cast<float>(zdarzenie.size.height));
					oknoGlowne_->setView(sf::View(visibleArea));
				}
				break;
				}

				for (auto ekran : stosEkranow_)
					ekran->odbierz(stan, zdarzenie);
			}
		}
	}

	void OknoGry::uaktualnianie(Stan& stan){
		static const Stan::KrokCzasu krok(30);
		Stan::KrokCzasu accumulator = stan.dt_;
		while (accumulator > krok){
			for (auto ekran : stosEkranow_)
				ekran->uaktualnij(stan);
			accumulator -= krok;
		}
		stan.dt_ = accumulator;
	}

	void OknoGry::odmaluj(){
		if (oknoGlowne_) {
			oknoGlowne_->clear(sf::Color(255, 255, 255, 0));

			for (auto ekran : stosEkranow_)
				ekran->pobierzGUI().draw();

			oknoGlowne_->display();
		}
	}

	void OknoGry::zakmnij(){
		przetwarzanie_ = false;
	}

	std::string OknoGry::napis() const{
		SLog::Logger logger(NAZWAKLASY(OknoGry));

		std::stringstream streamPrzetwarzanie;
		streamPrzetwarzanie.imbue(std::locale());
		streamPrzetwarzanie << std::boolalpha << przetwarzanie_;
		logger.dodajPole(NAZWAPOLA(przetwarzanie_), NAZWAKLASY2(przetwarzanie_), streamPrzetwarzanie.str());
		
		std::stringstream streamBoolPauza_;
		streamBoolPauza_.imbue(std::locale());
		streamBoolPauza_ << std::boolalpha << boolPauza_;
		logger.dodajPole(NAZWAPOLA(boolPauza_), NAZWAKLASY2(boolPauza_), streamBoolPauza_.str());

		logger.rozpocznijPodKlase(NAZWAPOLA(listaEkranow_), "MapaEkranow");
		for (auto& element : listaEkranow_){
			logger.rozpocznijPodKlase("Para");
			logger.dodajPole("first", element.first);
			if (element.second != nullptr){
				logger.dodajPole("second", element.second);
			}
			else{
				logger.dodajPole("second", NAZWAKLASY2(element.second), "nullptr");
			}
			logger.zakonczPodKlase();
		}
		logger.zakonczPodKlase();

		logger.rozpocznijPodKlase(NAZWAPOLA(stosEkranow_), "StosEkranow");
		for (auto& element : stosEkranow_){
			if (element != nullptr){
				logger.dodajPole(NAZWAPOLA(element), element);
			}
			else{
				logger.dodajPole(NAZWAPOLA(element), NAZWAKLASY2(element), "nullptr");
			}
		}
		logger.zakonczPodKlase();

		return logger.napis();
	}
};
