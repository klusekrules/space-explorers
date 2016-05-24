#pragma once
#include "BaseSide.h"

namespace SpEx {
	class KlientSideMulti :
		public BaseSide
	{
	public:
		// Konstruktor po stronie klienta.
		KlientSideMulti(const UstawieniaAplikacji& opcje);

		// Konstruktor po stronie klienta.
		KlientSideMulti(const std::string& ip, unsigned short port);

		KlientSideMulti(SOCKET, struct sockaddr_in&);

		std::future<bool> dodajZadanie(std::shared_ptr<std::promise<bool> >, std::shared_ptr<const std::string>, std::shared_ptr<std::string>, int);
	
	private:

		struct Zadanie {
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

		void pracujJakoKlient();
	};
}

