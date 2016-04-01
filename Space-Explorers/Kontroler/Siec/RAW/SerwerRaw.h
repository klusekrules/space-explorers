#pragma once
#include "Kontroler\Wielowatkowosc\Watek.h"
#include <WinSock2.h>

namespace SpEx {
	class SerwerRaw :
		public Watek
	{
	public:
		SerwerRaw(const std::string&,FILE*);
		u_short getPort() const;
		virtual ~SerwerRaw();
	private:
		SOCKET gniazdo_;
		u_short port_;
		FILE* fp_;
		std::string nazwaPliku_;
		void wykonuj() override;
		bool SendData(SOCKET,void*, int) const;
		bool SendFile(SOCKET) const;
	};
}
