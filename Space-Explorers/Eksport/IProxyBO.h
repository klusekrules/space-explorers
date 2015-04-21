#pragma once
#include "TypyEksportowane.h"

namespace SpEx{
	class IProxyBO
	{
	public:
		IProxyBO() = default;

		~IProxyBO() = default;

		virtual int uruchomSerwer() = 0;

		virtual int zatrzymajSerwer() = 0;

		virtual int polaczDoSerwera(const char* ip, unsigned short port) = 0;

		virtual int rozlaczOdSerwera() = 0;

		virtual int posptrzataj() = 0;

		virtual int rejestrujMetodyKonsoli() = 0;

		virtual TrybAplikacji pobierzTrybAplikacji() = 0;
	};
};
