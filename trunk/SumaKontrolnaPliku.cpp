#include "SumaKontrolnaPliku.h"
#pragma warning( disable : 4996 )
namespace SpEx{

	SumaKontrolnaPliku::SumaKontrolnaPliku(const std::string& plik)
		: sumaKontrolna_(fopen(plik.c_str(),"rb"))
	{}

	bool SumaKontrolnaPliku::inicjalizuj(){
		return true;
	}

	bool SumaKontrolnaPliku::Rejestruj(ZarzadcaZasobow &fabryka){
		return fabryka.rejestrujInicjalizator(TYP_ZASOBU_SUMA_KONTROLNA_PLIKU, SumaKontrolnaPliku::Tworz);
	}

	Zasob::SharedPtr SumaKontrolnaPliku::Tworz(const ZarzadcaZasobow::Parametr& parametr, bool cache){
		return std::make_shared<SumaKontrolnaPliku>(parametr);
	}

}