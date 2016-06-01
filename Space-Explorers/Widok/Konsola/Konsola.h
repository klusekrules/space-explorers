#pragma once
#include "Kontroler\Wielowatkowosc\Watek.h"
#include "Narzedzia\UstawieniaAplikacji.h"
#include "Logger\Log.h"
#include "TGUI\TGUI.hpp"
#include <future>

#define WDG_WIDGETS_DONT_FIND -1
#define WDG_THROW_STYP -2
#define WDG_THROW_TGUI -3
#define WDG_THROW_STD -4
#define WDG_THROW_UNKNOWN -5

namespace SpEx{
	class Konsola :
		public Watek
	{
	public:
		struct OpcjePolecenia{
			OpcjePolecenia(std::string opis, std::function<void(std::string)> funkcja)
				: opisPolecenia_(opis), funkcja_(funkcja){}

			std::string opisPolecenia_;
			std::function<void(std::string)> funkcja_;
		};
		
		Konsola(SLog::Log& log, UstawieniaAplikacji& ustawienia);
		void wykonuj() override;
		void dodajKomunikat(const std::string&, const sf::Color&);
		bool czekajNaInicjalizacje();
		bool przesunNaWierch() const;
		void rejestrujPolecenie(const std::string&, const OpcjePolecenia&);
		void Konsola::logujListePolecen() const;
		virtual ~Konsola() = default;
	private:
		void wykonajPolecenie(const std::string& polecenie) const;
		void callback(tgui::ChatBox::Ptr chatbox, const tgui::Callback& callback) const;

		struct Komunikat{
			std::string komunikat_;
			sf::Color kolor_;
		};

		std::map< std::string, OpcjePolecenia> poleceniaKonsoli_;
		std::unique_ptr<sf::RenderWindow> ptrWindow = nullptr;

		std::list<Komunikat> lista_;
		std::mutex muxLista_;
		std::promise<bool> inicjalizacja_; /// Przypisanie informacji o wyniku inicjalizacji.
		std::future<bool> inicjalizacjaWynik_; /// Wynik inicjalizacji.
		SLog::Log& log_;

		//Parametry konfiguracyjne.
		std::string plikWdg_;
		std::string plikCzcionki_;
		std::string nazwaEditbox_;
		std::string nazwaChatbox_;
		std::string tytulOkna_;
		unsigned int szerokoscOkna_ = 650;
		unsigned int wysokoscOkna_ = 400;
		int pozycjaX_ = 10;
		int pozycjaY_ = 10;
	};
}
