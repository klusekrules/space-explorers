#include "SumaKontrolnaPliku.h"
#include "Logger\Logger.h"
#pragma warning( disable : 4996 )
namespace SpEx{
	const std::string SumaKontrolnaPliku::NazwaTypu_ = "fileSHA3";

	SumaKontrolnaPliku::SumaKontrolnaPliku(const std::string& plik)
		: plik_(plik), fp_(fopen(plik.c_str(), "rb")), sumaKontrolna_(fp_)
	{
		fclose(fp_);
		fp_ = nullptr;
	}
	
	bool SumaKontrolnaPliku::inicjalizuj(){
		return true;
	}

	std::string SumaKontrolnaPliku::napis() const{
		SLog::Logger log(NAZWAKLASY(SumaKontrolnaPliku));
		log.dodajPole(NAZWAPOLA(plik_), "std::string", plik_);
		log.dodajPole(NAZWAPOLA(sumaKontrolna_), NAZWAKLASY2(sumaKontrolna_), sumaKontrolna_.pobierzNapis());
		return std::move(log.napis());
	}
	
}