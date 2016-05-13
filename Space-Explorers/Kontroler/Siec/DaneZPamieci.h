#pragma once
#include "IDane.h"
#include <vector>

#define ROZMIAR_BUFFORA 1500

namespace SpEx {
	class DaneZPamieci
		: public IDane
	{
	public:
		DaneZPamieci() = default;
		virtual ~DaneZPamieci() = default;
		unsigned __int64 rozmiar() const override;
	protected:
		std::vector<char> buffor_;

		int wyslij(GniazdoWinSock& e, int flagi) override;
		int odbierz(GniazdoWinSock& e, int flagi) override;
	};
}