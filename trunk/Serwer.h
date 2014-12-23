#pragma once
#include "Watek.h"
#include "UstawieniaAplikacji.h"

namespace SpEx{
	class Serwer :
		public Watek
	{
	public:
		Serwer(const UstawieniaAplikacji& opcje);
		virtual ~Serwer();
	};
}
