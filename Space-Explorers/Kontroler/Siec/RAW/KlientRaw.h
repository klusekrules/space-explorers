#pragma once
#include "Kontroler\Wielowatkowosc\Watek.h"
#include "Kontroler\Siec\SocketBase.h"
#include <WinSock2.h>
#include "../Klient.h"

namespace SpEx {
	class KlientRaw :
		public Watek,
		public SocketBase
	{
	public:
		KlientRaw(Klient& ref, const std::string&, const std::string&, u_short);
		virtual ~KlientRaw() = default;
	private:
		int error_;
		Klient& ref_;
		std::string nazwaPliku_;
		void wykonuj() override;
	};
}