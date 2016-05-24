#pragma once
#include "Kontroler\Wielowatkowosc\Watek.h"
#include "..\Nasluchiwacz.h"
#include "Narzedzia\UstawieniaAplikacji.h"
#include <WinSock2.h>
#include "SerwerSideMulti.h"
#include <list>

namespace SpEx{
	class SerwerMulti :
		public Nasluchiwacz
	{
	public:
		SerwerMulti(const UstawieniaAplikacji& opcje);
		virtual ~SerwerMulti() = default;
	private:
		SOCKET gniazdo_;
		void wykonuj() override;
		bool polaczeniePrzychodzace(SOCKET, struct sockaddr_in&) override;
		std::list<SerwerSideMulti> polaczenia_;
		void clear();
	};
}
