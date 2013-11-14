#include "Watek.h"
#include <Windows.h>

Watek::Watek(void)
	: zakonczony_(false), zakoncz_(false)
{
	uchwyt_ = new std::thread(&Watek::funkcjaWatku,this);
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

bool Watek::zakonczony(){
	return zakonczony_;
}

bool Watek::czyZakonczyc(){
	return zakoncz_;
}

void Watek::wykonuj(){
	while(czyZakonczyc()){
		std::this_thread::yield();
	}
}

void Watek::funkcjaWatku(){
	try{
		wykonuj();
	}catch(...){
		zakonczony_=true;
		ExitThread(-1);
	}
	zakonczony_=true;
	ExitThread(ERROR_SUCCESS);
}