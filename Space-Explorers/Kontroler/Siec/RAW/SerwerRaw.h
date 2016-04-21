#pragma once
#include "Kontroler\Wielowatkowosc\Watek.h"
#include "Kontroler\Siec\Nasluchiwacz.h"
#include <WinSock2.h>

namespace SpEx {
	class SerwerRaw :
		public Nasluchiwacz
	{
	public:
		SerwerRaw(const std::string&,FILE*);
		virtual ~SerwerRaw();
	private:
		int error_;
		FILE* fp_;
		std::string nazwaPliku_;
		bool SendData(SOCKET, void*, int);
		bool SendFile(SOCKET);
		bool polaczeniePrzychodzace(SOCKET, struct sockaddr_in&) override;
	};
}
