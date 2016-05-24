#pragma once
#include "Kontroler\Wielowatkowosc\Watek.h"
#include "Kontroler\Siec\Nasluchiwacz.h"
#include <WinSock2.h>
#include "BaseSide.h"

namespace SpEx {
	class SerwerOnce :
		public Nasluchiwacz
	{
	public:
		SerwerOnce(BaseSide& ref, const std::string&);
		virtual ~SerwerOnce() = default;
	private:
		std::string nazwaPliku_;
		BaseSide& ref_;
		bool polaczeniePrzychodzace(SOCKET, struct sockaddr_in&) override;
	};
}
