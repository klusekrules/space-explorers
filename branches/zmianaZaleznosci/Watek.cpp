#include "Watek.h"
#include <Windows.h>

Watek::Watek( bool wstrzymany )
	: zakonczony_(false), zakoncz_(false)
{
	if(wstrzymany)
		wstrzymany_.lock();
	uchwyt_ = new std::thread(&Watek::funkcjaWatku,this);
}

void Watek::odblokuj(){
	wstrzymany_.unlock();
}

bool Watek::czekajNaZakonczenie(){
	if(uchwyt_->joinable()){
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
	zakoncz_=true;
}

std::atomic<bool>& Watek::zakonczony(){
	return zakonczony_;
}

std::atomic<bool>& Watek::czyZakonczyc(){
	return zakoncz_;
}

void Watek::wykonuj(){
	std::this_thread::yield();
}

void Watek::funkcjaWatku(){	
	try{
		std::lock_guard<std::mutex> blokada(wstrzymany_);
		wykonuj();
	}catch(...){
		zakonczony_=true;
		ExitThread(-1);
	}
	zakonczony_=true;
	ExitThread(ERROR_SUCCESS);
}