#pragma once
#include "Kontroler\Wielowatkowosc\Watek.h"
#include "Nasluchiwacz.h"
#include "Narzedzia\UstawieniaAplikacji.h"
#include <WinSock2.h>
#include "Klient.h"
#include <list>

namespace SpEx{
	class Serwer :
		public Nasluchiwacz
	{
	public:
		Serwer(const UstawieniaAplikacji& opcje);
		virtual ~Serwer() = default;
	private:
		SOCKET gniazdo_;
		void wykonuj() override;
		bool polaczeniePrzychodzace(SOCKET, struct sockaddr_in&) override;
		std::list<Klient> polaczenia_;
		void clear();
	};
}
