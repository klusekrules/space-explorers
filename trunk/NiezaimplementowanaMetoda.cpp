#include "NiezaimplementowanaMetoda.h"
#include "Logger\Logger.h"
#include "Aplikacja.h"

namespace SpEx{
	NiezaimplementowanaMetoda::NiezaimplementowanaMetoda(const STyp::Tekst& tPlik, const STyp::Tekst& funkcja, const STyp::Ilosc& iLinia)
		: Wyjatek(tPlik, funkcja, iLinia, Aplikacja::pobierzInstancje().pobierzSladStosu(), Aplikacja::pobierzInstancje().pobierzDebugInfo(), 
		idNiezaimplementowanaMetoda, tytulNiezaimplementowanaMetoda, trescNiezaimplementowanaMetoda + funkcja)
	{
	}
	
	std::string NiezaimplementowanaMetoda::napis() const{
		SLog::Logger str(NAZWAKLASY(NiezaimplementowanaMetoda));
		str.dodajKlase(Wyjatek::napis());
		return str.napis();
	}
}