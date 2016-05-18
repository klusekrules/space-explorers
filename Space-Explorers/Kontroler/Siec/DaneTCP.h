#pragma once
#include "IDane.h"
#include "GniazdoWinSock.h"

namespace SpEx {
	class DaneTCP {
	public:
		typedef std::function <bool(void)> Warunek;

		DaneTCP(GniazdoWinSock& gniazdo, IDane& dane, Warunek& warunek)
			: gniazdo_(gniazdo), dane_(dane), warunek_(warunek) {}

		int wyslij();
		int odbierz();

		virtual ~DaneTCP() = default;

	private:
		IDane& dane_;
		GniazdoWinSock& gniazdo_;
		Warunek& warunek_;
	};
}