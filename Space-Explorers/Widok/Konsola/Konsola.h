#pragma once
#include "Kontroler\Wielowatkowosc\Watek.h"
#include "Logger\Log.h"
#include "TGUI\TGUI.hpp"
#include <future>

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
		
		Konsola(SLog::Log& log);
		void wykonuj() override;
		void dodajKomunikat(const std::string&, const sf::Color&);
		bool czekajNaInicjalizacje();
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

		std::list<Komunikat> lista_;
		std::mutex muxLista_;
		std::promise<bool> inicjalizacja_; /// Przypisanie informacji o wyniku inicjalizacji.
		std::future<bool> inicjalizacjaWynik_; /// Wynik inicjalizacji.
		SLog::Log& log_;
	};
}
