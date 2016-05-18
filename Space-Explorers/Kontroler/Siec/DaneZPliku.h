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
		int przygotujDane() override;
	protected:
		FILE * plik_;
		unsigned __int64 rozmiar_;
		bool received_ = false;

		int wyslij(GniazdoWinSock& e, int flagi) override;
		int odbierz(GniazdoWinSock& e, int flagi) override;

	};
}