#include "Watek.h"
#include <Windows.h>
namespace SpEx{

	Watek::Watek(bool wstrzymany)
		: zakonczony_(false), zakoncz_(false), blad_(false), bladInfo_(EXCEPTION_PLACE, STyp::Tekst()), kodPowrotu_(0)
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

	const std::atomic<bool>& Watek::zakonczony() const{
		return zakonczony_;
	}

	const std::atomic<bool>& Watek::czyZakonczyc() const{
		return zakoncz_;
	}
	
	const std::atomic<bool>& Watek::blad() const{
		return blad_;
	}
	
	const STyp::Wyjatek& Watek::bladInfo() const{
		return bladInfo_;
	}

	const std::atomic<int>& Watek::kodPowrotu() const{
		return kodPowrotu_;
	}

	void Watek::ustawBlad(const STyp::Wyjatek& info){
		bladInfo_ = info;
		blad_ = true;
	}
	
	void Watek::ustawKodPowrotu(int kod){
		kodPowrotu_ = kod;
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
