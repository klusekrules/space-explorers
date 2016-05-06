#pragma once
#include "IDane.h"
#include "IGniazdo.h"

namespace SpEx {
	class DaneTCP {
	public:
		typedef unsigned __int64 Flagi;
		typedef std::function <bool(void)> Warunek;

		DaneTCP(Flagi flagi, IGniazdo& gniazdo, IDane& dane, Warunek& warunek) 
			: flagi_(flagi), gniazdo_(gniazdo), dane_(dane), warunek_(warunek) {}

		int wyslij();
		int odbierz();

		virtual ~DaneTCP() = default;

	private:
		Flagi flagi_;
		IDane& dane_;
		IGniazdo& gniazdo_;
		Warunek& warunek_;
	};
}