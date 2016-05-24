#include "SerwerSideMulti.h"
#include "..\DaneJSON.h"

namespace SpEx {

	SerwerSideMulti::SerwerSideMulti(SOCKET gniazdo, struct sockaddr_in &addr)
		: KlientSideMulti(gniazdo, addr)
	{
		funkcja_ = std::bind(&SerwerSideMulti::pracujJakoSerwer, this);
	}

	void SerwerSideMulti::pracujJakoSerwer() {
		while (!czyZakonczyc()) {
			DaneJSON dane(*this);
			int error = dane.odbierz();
			if (error != RPC_OK) {
				if (error != SOCK_CONNECTION_CLOSED || error != WSAECONNRESET || error != WSAECONNABORTED || error != WSAENETRESET || error != WSAENETUNREACH || error != WSAENETDOWN)
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Zamkniêto po³¹czenie (nn) [" + std::to_string(error) + "]: " + pobierzAdres());
				else
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Klient::pracujJakoSerwer() -> B³¹d podczas odbierania danych: " + std::to_string(error));
				break;
			}

			error = dane.wykonajMetode();
			if (error != RPC_OK) {
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Klient::pracujJakoSerwer() -> B³¹d podczas przetwarzania danych: " + std::to_string(error));
			}

			error = dane.wyslij();
			if (error != RPC_OK) {
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Klient::pracujJakoSerwer() -> B³¹d podczas wysy³ania danych: " + std::to_string(error));
				break;
			}
		}
		shutdown();
	}
}