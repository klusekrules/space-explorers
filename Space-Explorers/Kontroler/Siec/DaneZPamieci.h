#pragma once
#include "IDane.h"
#include <vector>
#include "Klient.h"

#define ROZMIAR_BUFFORA 1500

namespace SpEx {
	class DaneZPamieci
		: public IDane
	{
	public:
		DaneZPamieci(Klient&);
		DaneZPamieci(Klient&,const std::string & dane);
		DaneZPamieci(Klient&, std::string && dane);
		virtual ~DaneZPamieci() = default;
		unsigned __int64 rozmiar() const override;
		int przygotujDane() override;
		const std::string& pobierzBufor() const;

	protected:
		std::string buffor_;
		Klient& ref_;
		bool received_ = false;
		int wyslij(GniazdoWinSock& e, int flagi) override;
		int odbierz(GniazdoWinSock& e, int flagi) override;
	};
}