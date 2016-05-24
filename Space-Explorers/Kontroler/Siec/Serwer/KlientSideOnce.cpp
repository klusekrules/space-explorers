#include "KlientSideOnce.h"
#include <Ws2tcpip.h>

#ifndef LOG_OFF_ALL
#include "Logger\Log.h"
#endif
#include "../DaneTCP.h"
#include "../DaneZPliku.h"

namespace SpEx {
	KlientSideOnce::KlientSideOnce(BaseSide& ref, const std::string& nazwaPliku, const std::string& ip, u_short port)
		: Watek("KlientSideOnce",true), nazwaPliku_(nazwaPliku), ref_(ref), SocketBase(port,1)
	{		
		ustawAdres(ip);
		socket();
	}
	
	void KlientSideOnce::wykonuj() {
		int error = connect();
		if (error != ERROR_SUCCESS) {
#ifndef LOG_OFF_ALL
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "KlientRaw::wykonuj() -> B³¹d funkcji connect: " + std::to_string(error));
#endif
			ustawKodPowrotu(error);
			return;
		}

		DaneZPliku dane(ref_,nazwaPliku_);
		auto gniazdo = std::move(pobierzGniazdo());
		DaneTCP::Warunek warunek([&]()->bool {return !this->czyZakonczyc(); });
		DaneTCP tcp(gniazdo, dane, warunek);

		error = tcp.odbierz();
		
		if (error != ERROR_SUCCESS) {
#ifndef LOG_OFF_ALL
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "KlientRaw::wykonuj() -> B³¹d funkcji RecvFile: " + std::to_string(error));
#endif
			ustawKodPowrotu(error);
			return;
		}
		ustawKodPowrotu(ERROR_SUCCESS);
	}
}
