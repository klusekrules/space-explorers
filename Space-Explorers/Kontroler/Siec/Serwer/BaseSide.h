#pragma once
#include "Kontroler\Wielowatkowosc\Watek.h"
#include "Narzedzia\UstawieniaAplikacji.h"
#include <WinSock2.h>
#include <future>
#include <list>
#include "Model\Uzytkownik.h"
#include "..\SocketBase.h"
#include "..\GniazdoWinSock.h"

namespace SpEx{

	class BaseSide :
		public Watek,
		public SocketBase
	{
	public:
		void autoryzujMetode(std::string& instancja, std::string& autoryzacja) const;

		bool czyAutoryzowany()const;

		void ustawKlucz(const std::string&);
		void ustawAutoryzacje(const std::string&);
		void ustawInstancje(const std::string&);

		const std::string& pobierzKlucz() const;
		
		const std::atomic<bool>& czyCzekaNaZakonczenie() const;
		
		virtual ~BaseSide();
	protected:

		BaseSide(std::string nazwa);
		BaseSide(std::string nazwa, SOCKET socket, struct sockaddr_in& addr);

		std::function<void(void)> funkcja_;
	private:
		std::string hash_;

		std::string autoryzacja_ = "0";
		std::string instancja_ = "0";

		std::shared_ptr<Uzytkownik> uzytkownik_;


		void wykonuj() override;

	};
}
