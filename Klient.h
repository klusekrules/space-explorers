#pragma once
#include "Watek.h"
#include "UstawieniaAplikacji.h"

namespace SpEx{
	class Klient :
		public Watek
	{
	public:
		Klient(const UstawieniaAplikacji& opcje);
		virtual ~Klient();
	};
}
