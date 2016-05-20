#pragma once
#include "Kontroler\Wielowatkowosc\Watek.h"
#include "Kontroler\Siec\Nasluchiwacz.h"
#include <WinSock2.h>
#include "../Klient.h"

namespace SpEx {
	class SerwerRaw :
		public Nasluchiwacz
	{
	public:
		SerwerRaw(Klient& ref, const std::string&);
		virtual ~SerwerRaw() = default;
	private:
		std::string nazwaPliku_;
		Klient& ref_;
		bool polaczeniePrzychodzace(SOCKET, struct sockaddr_in&) override;
	};
}
