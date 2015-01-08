#include "ProceduraRPC.h"

namespace SpEx{
	ProceduraRPC::ProceduraRPC()
	{
	}
	
	bool ProceduraRPC::wykonaj(){
		//Wyœlij przez otwarte po³¹czenie polecenie i czekaj na odpowiedŸ.
		
		// Polecenie do wys³ania
		Json::Value procedura;
		procedura["autorycazja"] = autoryzacja_;
		procedura["instancja"] = instancja_;
		komunikat_ >> procedura["metoda"];
		Json::FastWriter writer;
		auto daneWyslane = writer.write(procedura);

		// Wyslij dane

		// Odebrana informacja
		Json::Value odpowiedz;
		std::string daneOdebrane;
		Json::Reader reader;

		//Odbierz dane


		reader.parse(daneOdebrane, odpowiedz);
		odpowiedz_ << odpowiedz["metoda"];
		return true;
	}

	ProceduraRPC::~ProceduraRPC()
	{
	}
}
