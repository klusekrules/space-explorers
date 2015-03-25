#pragma once
#include "Watek.h"

namespace SpEx{
	class Konsola :
		public Watek
	{
	public:
		Konsola();
		void wykonuj() override;
		virtual ~Konsola();
	};
}
