#pragma once
#include "Kontroler\Wielowatkowosc\Watek.h"
#include "Kontroler\Siec\SocketBase.h"
#include <WinSock2.h>
#include "BaseSide.h"

namespace SpEx {
	class KlientSideOnce :
		public Watek,
		public SocketBase
	{
	public:
		KlientSideOnce(BaseSide& ref, const std::string&, const std::string&, u_short);
		virtual ~KlientSideOnce() = default;
	private:
		BaseSide& ref_;
		std::string nazwaPliku_;
		void wykonuj() override;
	};
}