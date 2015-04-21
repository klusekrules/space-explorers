#pragma once
#include "IProxyBO.h"
#include <memory>

namespace SpEx{
	class Klient;
};

namespace SpEx{
	class ProxyBOKlient :
		public IProxyBO
	{
	public:
		ProxyBOKlient() = default;

		~ProxyBOKlient() = default;

		int uruchomSerwer() override;

		int zatrzymajSerwer() override;

		int polaczDoSerwera(const char* ip, unsigned short port) override;

		int rozlaczOdSerwera() override;

		int posptrzataj() override;

		int rejestrujMetodyKonsoli() override;

		TrybAplikacji pobierzTrybAplikacji() override;

	private:
		std::shared_ptr<Klient> klient_;
	};
}