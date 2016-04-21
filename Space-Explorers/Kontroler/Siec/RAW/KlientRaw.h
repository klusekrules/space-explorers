#pragma once
#include "Kontroler\Wielowatkowosc\Watek.h"
#include "Kontroler\Siec\SocketBase.h"
#include <WinSock2.h>

namespace SpEx {
	class KlientRaw :
		public Watek,
		public SocketBase
	{
	public:
		KlientRaw(const std::string&, FILE*, const std::string&, u_short);
		virtual ~KlientRaw();
	private:
		int error_;
		FILE* fp_;
		std::string nazwaPliku_;
		void wykonuj() override;
		bool RecvData(void*, int);
		bool RecvFile();
	};
}