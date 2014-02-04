#include "WyjatekSprawdzeniaWarunku.h"
#include <sstream>

WyjatekSprawdzeniaWarunku::WyjatekSprawdzeniaWarunku(const std::string& tPlik, int iLinia, const std::string& oczekiwano, const std::string& otrzymano)
	: plik_(tPlik), linia_(iLinia), oczekiwano_(oczekiwano), otrzymano_(otrzymano)
{
}

void WyjatekSprawdzeniaWarunku::ustawNazweMetody(const std::string& t){
	nazwaMetody_ = t;
}

std::string WyjatekSprawdzeniaWarunku::komunikat() const{
	std::stringstream str;
	str << "B³¹d: " << plik_.substr(plik_.find_last_of('\\') + 1, std::string::npos) << ":" << linia_ << "; " << nazwaMetody_ << " - Oczekiwano: " << oczekiwano_ << "; Otrzymano: " << otrzymano_ << std::endl;
	return str.str();
}
