#pragma once
#include "MetodaRPC.h"

namespace SpEx{

	//Prawdopodobnie do usuniÍcia.
	class ProceduraRPC
	{
	public:
		ProceduraRPC();

		bool wykonaj();

		~ProceduraRPC();
	private:
		std::string autoryzacja_;
		std::string instancja_;
		
		//MetodaRPC komunikat_;
		//MetodaRPC odpowiedz_;

	};
}
