#include "SumaKontrolnaPliku.h"
#pragma warning( disable : 4996 )
namespace SpEx{
	const std::string SumaKontrolnaPliku::NazwaTypu_ = "fileSHA3";

	SumaKontrolnaPliku::SumaKontrolnaPliku(const std::string& plik)
		: sumaKontrolna_(fopen(plik.c_str(),"rb"))
	{
	}
	
	bool SumaKontrolnaPliku::inicjalizuj(){
		return true;
	}
	
}