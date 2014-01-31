#pragma once
#include <string>

class WyjatekSprawdzeniaWarunku
{
public:
	WyjatekSprawdzeniaWarunku(const std::string& tPlik, int iLinia, const std::string& oczekiwano, const std::string& otrzymano);
	~WyjatekSprawdzeniaWarunku();

	void ustawNazweMetody(const std::string&);
	std::string komunikat() const;

private:
	std::string plik_;
	int linia_;
	std::string oczekiwano_;
	std::string otrzymano_;
	std::string nazwaMetody_;
};
