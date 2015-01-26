#pragma once
#include "Watek.h"
#include "UstawieniaAplikacji.h"
#include <WinSock2.h>
#include "Klient.h"
#include <list>

namespace SpEx{
	class Serwer :
		public Watek
	{
	public:
		Serwer(const UstawieniaAplikacji& opcje);
		virtual ~Serwer();
	private:
		SOCKET gniazdo_;
		void wykonuj() override;
		std::list<Klient> polaczenia_;
	};
}