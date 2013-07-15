#include "WyjatekSprawdzeniaWarunku.h"
#include <sstream>

WyjatekSprawdzeniaWarunku::WyjatekSprawdzeniaWarunku( const string& tPlik, int iLinia, const string& oczekiwano, const string& otrzymano )
	: plik_(tPlik), linia_(iLinia), oczekiwano_(oczekiwano), otrzymano_(otrzymano)
{
}

WyjatekSprawdzeniaWarunku::~WyjatekSprawdzeniaWarunku()
{
}

void WyjatekSprawdzeniaWarunku::ustawNazweMetody( const string& t ){
	nazwaMetody_ = t;
}

string WyjatekSprawdzeniaWarunku::komunikat() const{
	stringstream str;
	str << "B³¹d: "<<plik_.substr(plik_.find_last_of('\\')+1,string::npos) << ":" <<  linia_ <<"; "<< nazwaMetody_ << " - Oczekiwano: " << oczekiwano_ << "; Otrzymano: "<< otrzymano_<<endl;		
	return str.str();
}
