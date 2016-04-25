#include "WatekZarzadzany.h"

namespace SpEx{
	WatekZarzadzany::WatekZarzadzany(std::future<bool> wykonuj)
		: Watek("WatekZarzadzany", true), nastepneNoweZadanie_(std::move(wykonuj))
	{
	}

	void WatekZarzadzany::dodajZadanie(Zadanie& zadanie, std::future<bool> noweZadanie){
		std::lock_guard<std::mutex> blokadaFlagi(mutexNastepneNoweZadanie_);
		std::lock_guard<std::mutex> blokadaZadania(mutexZadanie_);
		nastepneNoweZadanie_ = std::move(noweZadanie);
		zadania_.push_back(std::move(zadanie));
	}

	void WatekZarzadzany::wykonuj(){
		while (!czyZakonczyc()){
			Zadanie zadanie;
			if (pobierzZadanie(zadanie)){
				zadanie.wykonaj();
			}
			else{
				ustawOczekiwanieNaNoweZadanie();
				noweZadanie_.wait();
				if (!noweZadanie_.get())
					break;
			}
		}
	}

	bool WatekZarzadzany::pobierzZadanie(Zadanie& zadanie){
		std::lock_guard<std::mutex> blokadaZadania(mutexZadanie_);
		if (zadania_.empty())
			return false;
		zadanie = std::move(zadania_.front());
		zadania_.pop_front();
		return true;
	}

	void WatekZarzadzany::ustawOczekiwanieNaNoweZadanie(){
		std::lock_guard<std::mutex> blokadaZadania(mutexNastepneNoweZadanie_);
		noweZadanie_ = std::move(nastepneNoweZadanie_);
	}
};