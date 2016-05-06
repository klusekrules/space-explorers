#pragma once
#include "IDane.h"
#include <string>

#define ROZMIAR_BUFFORA 1500

namespace SpEx {
	class DaneZPliku
		: public IDane
	{
	public:
		DaneZPliku(const std::string& adresPliku);
		virtual ~DaneZPliku();
		unsigned __int64 rozmiar() const override;
		int wez(const char * dane, unsigned __int64 rozmiar) override;
		int daj(const char ** dane, unsigned __int64& rozmiar) override;
	protected:
		FILE * plik_;
		unsigned __int64 rozmiar_;
		char buffor_[ROZMIAR_BUFFORA];
	};
}