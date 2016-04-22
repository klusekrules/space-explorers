#pragma once
#include "SocketBase.h"
#include "Kontroler\Wielowatkowosc\Watek.h"
#include <list>

namespace SpEx {
	class Nasluchiwacz
		: public SocketBase, public Watek
	{
	public:
		Nasluchiwacz();
		Nasluchiwacz(const UstawieniaAplikacji& opcje);
		void ustawAcceptTimeout(long timeout);
		long pobierzAcceptTimeout()const;

		virtual ~Nasluchiwacz();
	protected:
		void wykonuj() override;
	private:
		virtual bool polaczeniePrzychodzace(SOCKET, struct sockaddr_in&) = 0;
		void init();
		int port_ = 0;
		long acceptTimeout_ = 0;
		int maxIloscPolaczen_ = SOMAXCONN;
		SOCKET gniazdo_ = INVALID_SOCKET;
	};
}