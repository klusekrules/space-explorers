#include "MenadzerWatkow.h"

MenadzerWatkow::ElementListy::ElementListy()
	: sygnal_()
{
	watek_ = std::make_shared<WatekZarzadzany>(sygnal_.get_future());
	watek_->odblokuj();
}

MenadzerWatkow::ElementListy::ElementListy( ElementListy&& e ) 
	: watek_(std::move(e.watek_)), sygnal_(std::move(e.sygnal_))
{
}

MenadzerWatkow::ElementListy::~ElementListy(){
	if(watek_){
		watek_->zakoncz();
		sygnal_.set_value(false);
		watek_->czekajNaZakonczenie();
	}
}

void MenadzerWatkow::ElementListy::dodajZadanie( Zadanie& zadanie ){
	std::promise<bool> nowySygnal;
	watek_->dodajZadanie(zadanie,nowySygnal.get_future());
	sygnal_.swap(nowySygnal);
	nowySygnal.set_value(true);
}

MenadzerWatkow::~MenadzerWatkow()
{
}

MenadzerWatkow::MenadzerWatkow( char iloscWatkow )
{
	numerWatku_ = 0;
	pulaWatkow_.reserve(iloscWatkow);
	for( int i = 0; i < iloscWatkow ; ++i)
		pulaWatkow_.emplace_back();
}

void MenadzerWatkow::dodajZadanie( Zadanie& zadanie ){
	std::lock_guard<std::mutex> blokada(mutaxPuliWatkow_);
	pulaWatkow_[numerWatku_].dodajZadanie(zadanie);
	numerWatku_ = ( numerWatku_ + 1 ) % pulaWatkow_.size();
}