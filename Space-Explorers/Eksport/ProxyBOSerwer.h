#pragma once
#include "IProxyBO.h"
#include <memory>

namespace SpEx{
	class Serwer;
};

namespace SpEx{
	class ProxyBOSerwer :
		public IProxyBO
	{
	public:
		ProxyBOSerwer();

		~ProxyBOSerwer() = default;

		int uruchomSerwer() override;

		int zatrzymajSerwer() override;

		int polaczDoSerwera(const char* ip, unsigned short port) override;

		int rozlaczOdSerwera() override;

		int posptrzataj() override;
		
		int rejestrujMetodyKonsoli() override;

		int zaloguj(const char * nazwa, const char* hash) override;
		
		int sprawdzPoprawnoscPlikow() override;

		TrybAplikacji pobierzTrybAplikacji() override;

		int pobierzPlikiGry() override;

	private:
		std::shared_ptr<Serwer> serwer_;

	};
}