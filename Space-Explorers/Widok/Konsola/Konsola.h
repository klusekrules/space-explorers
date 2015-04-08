#pragma once
#include "Kontroler\Wielowatkowosc\Watek.h"
#include "Logger\Log.h"
#include "TGUI\TGUI.hpp"

namespace SpEx{
	class Konsola :
		public Watek
	{
	public:
		Konsola(SLog::Log& log);
		void wykonuj() override;
		void dodajKomunikat(const std::string& , const sf::Color&);
		virtual ~Konsola();
	private:
		struct Komunikat{
			std::string komunikat_;
			sf::Color kolor_;
		};
		std::list<Komunikat> lista_;
		std::mutex muxLista_;
	};
}
