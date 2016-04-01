#pragma once
#include "Kontroler\Wielowatkowosc\Watek.h"
#include <WinSock2.h>

namespace SpEx {
	class KlientRaw :
		public Watek
	{
	public:
		KlientRaw(const std::string&, FILE*, const std::string&, u_short);
		virtual ~KlientRaw();
	private:
		SOCKET gniazdo_;
		u_short port_;
		FILE* fp_;
		struct sockaddr_in addr_;
		std::string nazwaPliku_;
		void wykonuj() override;
		bool RecvData(SOCKET, void*, int) const;
		bool RecvFile(SOCKET) const;
	};
}