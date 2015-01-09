#pragma once
#include "Watek.h"
#include "UstawieniaAplikacji.h"
#include <WinSock2.h>

namespace SpEx{
	class Klient :
		public Watek
	{
	public:

		// Konstruktor po stronie klienta.
		Klient(const UstawieniaAplikacji& opcje);


		// Konstruktor po stronie serwera.
		Klient(SOCKET gniazdo, struct sockaddr_in &addr);
		void zamknijPolaczenie();
		virtual ~Klient();
	private:
		SOCKET gniazdo_ = INVALID_SOCKET;
		struct sockaddr_in addr_;		
		std::function<void(void)> funkcja_;

		void odbieraj();
		void wysylaj();
		void wykonuj() override;

		bool wyslij(const std::string&, int&);
		bool odbierz(std::string&, int&);
	};
}
