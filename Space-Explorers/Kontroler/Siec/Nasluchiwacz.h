#pragma once
#include "SocketBase.h"
#include "Kontroler\Wielowatkowosc\Watek.h"
#include <list>

namespace SpEx {
	class Nasluchiwacz
		: public SocketBase, public Watek
	{
	public:
		Nasluchiwacz() = default;
		Nasluchiwacz(const UstawieniaAplikacji& opcje);
		void wykonuj() override;
		virtual ~Nasluchiwacz();
		virtual bool polaczeniePrzychodzace(SOCKET, struct sockaddr_in&) = 0;
	private:
		int port_ = 0;
		int maxIloscPolaczen_ = SOMAXCONN;
		SOCKET gniazdo_ = INVALID_SOCKET;
	};
}