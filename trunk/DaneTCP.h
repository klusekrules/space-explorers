#pragma once 
#include "MetodaRPC.h"

namespace SpEx{
	class DaneTCP{
	public:
		DaneTCP(Klient&);
		DaneTCP(Klient&, const std::string&, std::string&, int);

		bool odbierz();
		bool wyslij();

		bool wykonajMetode();
		
		void wlaczKompresje();
		void wlaczAutoryzacje();
		~DaneTCP() = default;
	private:

		bool odbierzWewnetrzna();
		bool wyslijWewnetrzna();
		int przygotujDoWyslania();
		int przetworzPoOdebraniu();
		bool kompresja();
		bool dekompresja();
		bool szyfrowanie(const std::string& klucz);
		bool deszyfrowanie(const std::string& klucz);
		void dodajKomunikatBledu(int, Json::Value&);

		Klient & ref_;
		u_int64 flagi_;
		std::string wyslij_;
		std::string& odbierz_;
		int error_;
	};
}