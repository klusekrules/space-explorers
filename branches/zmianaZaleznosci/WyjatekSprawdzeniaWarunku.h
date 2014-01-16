#pragma once
#include <string>
using namespace std;

class WyjatekSprawdzeniaWarunku
{
public:
	WyjatekSprawdzeniaWarunku( const string& tPlik, int iLinia, const string& oczekiwano, const string& otrzymano );
	~WyjatekSprawdzeniaWarunku();

	void ustawNazweMetody( const string& );
	string komunikat() const;

private:
	string plik_;
	int linia_;
	string oczekiwano_;
	string otrzymano_;
	string nazwaMetody_;
};
