#pragma once
#include "Watek.h"
#include "UstawieniaAplikacji.h"
#include <WinSock2.h>
#include <future>
#include <list>
#include "Parser\json\json.h"

namespace SpEx{
	class Klient :
		public Watek
	{
	public:
		// Konstruktor po stronie klienta.
		Klient(const UstawieniaAplikacji& opcje);

		// Konstruktor po stronie serwera.
		Klient(SOCKET gniazdo, struct sockaddr_in &addr);
		void zamknijPolaczenie();
		
		std::future<bool> dodajZadanie(std::shared_ptr<std::promise<bool> >, std::shared_ptr<const std::string>, std::shared_ptr<std::string>);

		void autoryzujMetode(std::string&, std::string&);

		virtual ~Klient();
	private:

		class Dane{
		public:
			Dane(Klient&);
			Dane(Klient&, std::string&&);
			bool odbierz(int & error);
			void wlaczKompresje();
			void wlaczAutoryzacje();
			int przygotujDoWyslania();
			int przetworzPoOdebraniu();
			bool wyslij(int & error);
			const std::string& pobierzDane();
			~Dane() = default;
		private:
			bool kompresja();
			bool dekompresja();
			bool szyfrowanie();
			bool deszyfrowanie();
			Klient & ref_;
			u_int64 flagi_;
			std::string dane_;
			int error_;
		};

		SOCKET gniazdo_ = INVALID_SOCKET;
		struct sockaddr_in addr_;		
		std::function<void(void)> funkcja_;

		std::string autoryzacja_ = "0";
		std::string instancja_ = "0";

		struct Zadanie{
			std::shared_ptr<std::promise<bool> > zakonczenie_;
			std::shared_ptr<const std::string> zadanie_;
			std::shared_ptr<std::string> rezultat_;

			Zadanie(std::shared_ptr<std::promise<bool> >zakonczenie, std::shared_ptr<const std::string> zadanie, std::shared_ptr<std::string> rezultat)
				: zakonczenie_(zakonczenie), zadanie_(zadanie), rezultat_(rezultat)
			{}
		};

		std::list<std::shared_ptr<Zadanie> > listaZadan_;
		std::mutex dostepDoZadan_;

		void wykonuj() override;

		void pracujJakoKlient();
		void pracujJakoSerwer();

		int sprawdzMetode(const Json::Value&) const;
		int sprawdzMetodeUprzywilejowana(const Json::Value&)const;
		int sprawdzAutoryzacje(const Json::Value&) const;
		void dodajKomunikatBledu(int, Json::Value&);
	};
}
