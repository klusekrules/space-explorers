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

		bool wyslij(const std::string&, int&);
		bool odbierz(std::string&, int&);


		void pracujJakoKlient();
		void pracujJakoSerwer();

		int sprawdzMetode(const Json::Value&) const;
		int sprawdzMetodeUprzywilejowana(const Json::Value&)const;
		int sprawdzAutoryzacje(const Json::Value&) const;
		void dodajKomunikatBledu(int, Json::Value&);
	};
}
