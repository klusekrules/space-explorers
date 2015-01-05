#pragma once
#include <string>
#include <vector>
#include "Parser\json\json.h"

namespace SpEx{
	class MetodaRPC
	{
	public:
		typedef std::pair<std::string, std::string> Parametr;

		MetodaRPC() = default;
		~MetodaRPC() = default;

		bool odczytajWezel(const Json::Value &);
	private:
		std::string id_;
		std::string nazwa_;
		std::string id_unikalne_;
		unsigned int powtorzenie_;
		std::string czas_wywolania_;
		std::string czas_odpowiedzi_;
		std::vector <Parametr> parametry_;
	};
}

