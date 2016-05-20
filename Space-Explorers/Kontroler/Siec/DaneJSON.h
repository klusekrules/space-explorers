#pragma once 
#include "RPC\MetodaRPC.h"

namespace SpEx{
	class DaneJSON {
	public:
		DaneJSON(Klient&);
		DaneJSON(Klient&, const std::string&, std::string&, int);

		int odbierz();
		int wyslij();

		int wykonajMetode();
		
		~DaneJSON() = default;
	private:
		void dodajKomunikatBledu(int, Json::Value&);

		Klient & ref_;
		u_int64 flagi_;
		std::string wyslij_;
		std::string& odbierz_;
		int error_;
	};
}