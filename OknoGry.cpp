#include "OknoGry.h"
#include "MaszynaStanow.h"
#include <SFML\OpenGL.hpp>
#include "EkranStartowy.h"
#include "definicjeWezlowXML.h"
#include "Aplikacja.h"
#include "FPSCounter.h"
#include "PowtorzenieIdObiektu.h"

#define KOMUNIKAT_POWTORZENIE_OBIEKTU(a) STyp::Tekst("Obiekt typu: "#a )
#define GL_SHADING_LANGUAGE_VERSION       0x8B8C
namespace SpEx{
	OknoGry::OknoGry(bool wstrzymany)
		: Watek(wstrzymany)
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
		for (auto& ekran : stosEkranow_){
			if (ekran){
				if (!!ekran->oknoKomunikatow_){
					ekran->oknoKomunikatow_->addMessage(typ,tresc);
					break;
				}
			}
		}
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
			return;
		}
		try{
			try{
				if (!inicjalizacja()){
					inicjalizacja_.set_value(false);
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d inicjalizacji.");
					return;
				}
			}
			catch (...){
				inicjalizacja_.set_value(false);
				throw;
			}
			std::lock_guard<std::mutex> blokada(mutexUruchom_);

			Stan::KrokCzasu accumulator;
			oknoGlowne_.setVisible(true);
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
			oknoGlowne_.close();
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
	}

	bool OknoGry::inicjalizacja(){
		std::lock_guard<std::mutex> blokada(mutexInicjalizacja_);
		przetwarzanie_ = false;
		logujInfo();
		oknoGlowne_.create(sf::VideoMode(800, 500), "Space-Explorers", sf::Style::None);
		oknoGlowne_.setVisible(false);
		oknoGlowne_.setVerticalSyncEnabled(true);

		oknoGlowne_.setVisible(false);

		SetWindowLong(oknoGlowne_.getSystemHandle(), GWL_EXSTYLE, GetWindowLong(oknoGlowne_.getSystemHandle(), GWL_EXSTYLE) | WS_EX_LAYERED);
		if (!SetLayeredWindowAttributes(oknoGlowne_.getSystemHandle(), NULL, 0, LWA_ALPHA)){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Nie dziala przezroczstosc.");
		}

		if (!wczytajEkrany()){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Nieuda³o siê wczytaæ ekranów.");
			return false;
		}

		inicjalizacja_.set_value(true);
		przetwarzanie_ = true;
		return true;
	}

	void OknoGry::logujInfo(){
		if (sf::Shader::isAvailable())
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Shadery dostepne");
		else{
			MessageBox(
				nullptr,
				"Karta graficzna nie wspiera shaderów.",
				"Fatal error",
				MB_ICONERROR
				);
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Shadery niedostepne");
		}

		char* p = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, p ? p : "");
		p = (char*)glGetString(GL_VERSION);
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, p ? p : "");
		p = (char*)glGetString(GL_VENDOR);
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, p ? p : "");
	}

	bool OknoGry::wczytajEkrany(){
		std::lock_guard<std::recursive_mutex> lock(mutexListaEkranow_);
		auto wezel = Aplikacja::pobierzInstancje().pobierzZarzadcePamieci().pobierzWezelKonfiguracyjnyOknaGry();
		if (wezel){
			XmlBO::ForEach<SpEx::STACKTHROW>(wezel, WEZEL_XML_EKRAN_STARTOWY, XmlBO::OperacjaWezla([&](XmlBO::ElementWezla element)->bool{
				auto ptr = std::make_shared<EkranStartowy>(oknoGlowne_, element); 
				if (listaEkranow_.find(ptr->pobierzId()) != listaEkranow_.end())
					throw PowtorzenieIdObiektu(EXCEPTION_PLACE, ptr->pobierzId(), KOMUNIKAT_POWTORZENIE_OBIEKTU(EkranStartowy));
				listaEkranow_.insert(std::make_pair(ptr->pobierzId(), ptr));
				return true;
			}));

			XmlBO::ForEach<SpEx::STACKTHROW>(wezel, WEZEL_XML_EKRAN, XmlBO::OperacjaWezla([&](XmlBO::ElementWezla element)->bool{
				auto ptr = std::make_shared<EkranSzablon>(element);
				if (listaEkranow_.find(ptr->pobierzId()) != listaEkranow_.end())
					throw PowtorzenieIdObiektu(EXCEPTION_PLACE, ptr->pobierzId(), KOMUNIKAT_POWTORZENIE_OBIEKTU(EkranSzablon));
				ptr->podlacz(oknoGlowne_);
				listaEkranow_.insert(std::make_pair(ptr->pobierzId(), ptr));
				return true;
			}));
		}
		return !listaEkranow_.empty();
	}
	
	void OknoGry::usunWszystkieEkrany(){
		for (auto ekran : listaEkranow_){
			ekran.second->odlacz(oknoGlowne_);
			ekran.second->clear();
		}
	}
	
	void OknoGry::przeladujEkran(const STyp::Identyfikator& id){
		std::lock_guard<std::recursive_mutex> lock(mutexListaEkranow_);
		auto iter = listaEkranow_.find(id);
		if (iter!= listaEkranow_.end()){
			auto wezel = Aplikacja::pobierzInstancje().pobierzZarzadcePamieci().pobierzWezelKonfiguracyjnyOknaGry();
			auto okno = XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel, WEZEL_XML_EKRAN, ATRYBUT_XML_IDENTYFIKATOR, id.napis());
			if (okno){
				auto ptr = std::make_shared<EkranSzablon>(okno);
				ptr->podlacz(oknoGlowne_);
				iter->second = ptr;
			}
		}
	}
	
	void OknoGry::obslugaZdarzen(Stan& stan){
		sf::Event zdarzenie;
		while (oknoGlowne_.pollEvent(zdarzenie))
		{
			switch (zdarzenie.type){
			case sf::Event::Closed:
				MaszynaStanow::pobierzInstancje().inicjujZamykanie();
				break;
			case sf::Event::MouseButtonPressed:
				SetActiveWindow(oknoGlowne_.getSystemHandle());
				break;
			case sf::Event::Resized:
			{
				sf::FloatRect visibleArea(0, 0, static_cast<float>(zdarzenie.size.width), static_cast<float>(zdarzenie.size.height));
				oknoGlowne_.setView(sf::View(visibleArea));
			}
				break;
			}

			for (auto ekran : stosEkranow_)
				ekran->odbierz(stan, zdarzenie);
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
		//static float balans = 0.0f;
		sf::RenderStates states;
		oknoGlowne_.clear(sf::Color(255, 255, 255, 0));

		for (auto ekran : stosEkranow_)
			oknoGlowne_.draw(*ekran);

		oknoGlowne_.display();
	}

	void OknoGry::zakmnij(){
		przetwarzanie_ = false;
	}
};
