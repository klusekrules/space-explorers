#include "MenedzerTranzakcji.h"
#include "NiepowodzenieTranzakcji.h"
#include "Aplikacja.h"

MenedzerTranzakcji::MenedzerTranzakcji()
{
}

MenedzerTranzakcji::~MenedzerTranzakcji()
{
}

void MenedzerTranzakcji::dodaj( Element operacja )
{
	if(operacja)
		listaOperacji_.emplace_back(operacja);
}

bool MenedzerTranzakcji::wykonaj()
{
	int iterator = 0;
	bool powodzenie = true;
	try{
		for(; iterator < static_cast<int>(listaOperacji_.size()); ++iterator){
			if(!listaOperacji_[iterator]->wykonaj()){
				powodzenie = false;
				break;
			}
		}
	}catch(OgolnyWyjatek& e){
		Aplikacja::pobierzInstancje().pobierzLogger().warn(e.generujKomunikat());
		powodzenie = false;
	}catch(std::exception& e){
		Aplikacja::pobierzInstancje().pobierzLogger().warn(e.what());
		powodzenie = false;
	}catch(...){
		powodzenie = false;
	}

	if(!powodzenie){
		try{
			for(--iterator; iterator >= 0; --iterator){
				if(!listaOperacji_[iterator]->cofnij()){
					throw NiepowodzenieTranzakcji(EXCEPTION_PLACE,listaOperacji_[iterator]->napis());
				}
			}
		}catch(NiepowodzenieTranzakcji& e){
			Aplikacja::pobierzInstancje().pobierzLogger().warn(e.generujKomunikat());
			throw;
		}catch(OgolnyWyjatek& e){
			Aplikacja::pobierzInstancje().pobierzLogger().warn(e.generujKomunikat());
			throw NiepowodzenieTranzakcji(EXCEPTION_PLACE,listaOperacji_[iterator]->napis());
		}catch(std::exception& e){
			Aplikacja::pobierzInstancje().pobierzLogger().warn(e.what());
			throw NiepowodzenieTranzakcji(EXCEPTION_PLACE,listaOperacji_[iterator]->napis());
		}catch(...){
			throw NiepowodzenieTranzakcji(EXCEPTION_PLACE,listaOperacji_[iterator]->napis());
		}
	}
	return powodzenie;
}

string MenedzerTranzakcji::napis() const{
	Logger str (NAZWAKLASY(MenedzerTranzakcji));
	for(const Element& element : listaOperacji_ ){
		str.dodajPole("Zlecenie", *element);
	}
	return str.napis();
}
