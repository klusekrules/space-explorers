#pragma once
#include "MetodaRPC.h"

namespace SpEx{
	class ProceduraRPC
	{
	public:
		ProceduraRPC();
		~ProceduraRPC();
	private:
		std::string autoryzacja_;
		std::string instancja_;
		
		MetodaRPC komunikat_;
		MetodaRPC odpowiedz_;

	};
}
