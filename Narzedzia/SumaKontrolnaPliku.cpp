#include "SumaKontrolnaPliku.h"
#include "Logger\Logger.h"
#include "Algorytmy\Hex.h"
#pragma warning( disable : 4996 )
namespace SpEx{
	const std::string SumaKontrolnaPliku::NazwaTypu_ = "sha3";

	SumaKontrolnaPliku::SumaKontrolnaPliku(const std::string& plik)
		: Zasob(plik), fp_(fopen(plik.c_str(), "rb")), sumaKontrolna_(fp_)
	{
		fclose(fp_);
		fp_ = nullptr;
	}
	
	bool SumaKontrolnaPliku::inicjalizuj(){
		return true;
	}

	std::string SumaKontrolnaPliku::napis() const{
		SLog::Logger log(NAZWAKLASY(SumaKontrolnaPliku));
		log.dodajPole(NAZWAPOLA(plik_), "std::string", pobierzAdresPliku());
		log.dodajPole(NAZWAPOLA(sumaKontrolna_), NAZWAKLASY2(sumaKontrolna_), sumaKontrolna_.pobierzNapis<Hex>());
		return std::move(log.napis());
	}
	
}