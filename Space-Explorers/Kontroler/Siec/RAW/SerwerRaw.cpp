#include "SerwerRaw.h"
#include <Ws2tcpip.h>

#ifndef LOG_OFF_ALL
#include "Logger\Log.h"
#endif

#include "../DaneTCP.h"
#include "../DaneZPliku.h"

namespace SpEx {
	SerwerRaw::SerwerRaw(Klient& ref,const std::string& nazwaPliku)
		: Nasluchiwacz(), ref_(ref), nazwaPliku_(nazwaPliku)
	{
		ustawAcceptTimeout(10);
	}
	
	bool SerwerRaw::polaczeniePrzychodzace(SOCKET soc, sockaddr_in &addr ){
		SocketBase base(soc, addr);

		DaneZPliku dane(ref_,nazwaPliku_);
		dane.ustawFlagi((unsigned __int64)FLAGA_WERSJA << 32 | FLAGA_SZYFROWANIE | FLAGA_KOMPRESJA);

		auto gniazdo = std::move(base.pobierzGniazdo());
		DaneTCP::Warunek warunek([&]()->bool { return !this->czyZakonczyc(); });
		DaneTCP tcp(gniazdo, dane, warunek);

		ustawKodPowrotu(tcp.wyslij());
		zakoncz();
		return false;
	}
}
