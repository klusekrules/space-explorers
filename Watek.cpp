#include "Watek.h"
#include <Windows.h>
namespace SpEx{

	Watek::Watek(bool wstrzymany)
		: zakonczony_(false), zakoncz_(false), blad_(false), bladInfo_(EXCEPTION_PLACE,STyp::Tekst())
	{
		if (wstrzymany)
			wstrzymany_.lock();
		uchwyt_ = new std::thread(&Watek::funkcjaWatku, this);
	}

	void Watek::odblokuj(){
		wstrzymany_.unlock();
	}

	bool Watek::czekajNaZakonczenie(){
		if (uchwyt_->joinable()){
			uchwyt_->join();
			return true;
		}
		return false;
	}

	Watek::~Watek(void)
	{
		delete uchwyt_;
	}

	void Watek::zakoncz(){
		zakoncz_ = true;
	}

	std::atomic<bool>& Watek::zakonczony(){
		return zakonczony_;
	}

	std::atomic<bool>& Watek::czyZakonczyc(){
		return zakoncz_;
	}
	
	std::atomic<bool>& Watek::blad(){
		return blad_;
	}
	
	STyp::Wyjatek& Watek::bladInfo(){
		return bladInfo_;
	}

	void Watek::ustawBlad(const STyp::Wyjatek& info){
		bladInfo_ = info;
		blad_ = true;
	}

	void Watek::wykonuj(){
		std::this_thread::yield();
	}

	void Watek::funkcjaWatku(){
		try{
			std::lock_guard<std::mutex> blokada(wstrzymany_);
			wykonuj();
		}
		catch (...){
			zakonczony_ = true;
			ExitThread(-1);
		}
		zakonczony_ = true;
		ExitThread(ERROR_SUCCESS);
	}
};
