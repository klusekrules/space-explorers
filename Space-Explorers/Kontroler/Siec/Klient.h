#pragma once
#include "Kontroler\Wielowatkowosc\Watek.h"
#include "Narzedzia\UstawieniaAplikacji.h"
#include <WinSock2.h>
#include <future>
#include <list>
#include "Model\Uzytkownik.h"
#include "SocketBase.h"
#include "GniazdoWinSock.h"

namespace SpEx{

	class Klient :
		public Watek,
		public SocketBase
	{
	public:
		// Konstruktor po stronie klienta.
		Klient(const UstawieniaAplikacji& opcje);

		// Konstruktor po stronie klienta.
		Klient(const std::string& ip, unsigned short port);

		// Konstruktor po stronie serwera.
		Klient(SOCKET gniazdo, struct sockaddr_in &addr);

		std::future<bool> dodajZadanie(std::shared_ptr<std::promise<bool> >, std::shared_ptr<const std::string>, std::shared_ptr<std::string>, int);

		void autoryzujMetode(std::string& instancja, std::string& autoryzacja) const;

		bool czyAutoryzowany()const;

		void ustawKlucz(const std::string&);
		void ustawAutoryzacje(const std::string&);
		void ustawInstancje(const std::string&);

		const std::string& pobierzKlucz() const;
		
		const std::atomic<bool>& czyCzekaNaZakonczenie() const;

		GniazdoWinSock pobierzGniazdo();

		virtual ~Klient();
	private:
		
		std::function<void(void)> funkcja_;

		std::string hash_;

		std::string autoryzacja_ = "0";
		std::string instancja_ = "0";

		std::shared_ptr<Uzytkownik> uzytkownik_;

		struct Zadanie{
			std::shared_ptr<std::promise<bool> > zakonczenie_;
			std::shared_ptr<const std::string> zadanie_;
			std::shared_ptr<std::string> rezultat_;
			int flagi_;

			Zadanie(std::shared_ptr<std::promise<bool> >zakonczenie, std::shared_ptr<const std::string> zadanie, std::shared_ptr<std::string> rezultat, int flagi)
				: zakonczenie_(zakonczenie), zadanie_(zadanie), rezultat_(rezultat), flagi_(flagi)
			{}
		};

		std::list<std::shared_ptr<Zadanie> > listaZadan_;
		std::mutex dostepDoZadan_;

		void wykonuj() override;

		void pracujJakoKlient();
		void pracujJakoSerwer();

	};
}
