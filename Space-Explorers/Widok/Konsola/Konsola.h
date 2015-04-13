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
		Konsola(SLog::Log& log);
		void wykonuj() override;
		void dodajKomunikat(const std::string&, const sf::Color&);
		bool czekajNaInicjalizacje();
		virtual ~Konsola();
	private:
		struct Komunikat{
			std::string komunikat_;
			sf::Color kolor_;
		};
		std::list<Komunikat> lista_;
		std::mutex muxLista_;
		std::promise<bool> inicjalizacja_; /// Przypisanie informacji o wyniku inicjalizacji.
		std::future<bool> inicjalizacjaWynik_; /// Wynik inicjalizacji.
	};
}
