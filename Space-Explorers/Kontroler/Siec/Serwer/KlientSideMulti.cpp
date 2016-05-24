#include "KlientSideMulti.h"
#include "Utils\Utils.h"
#include "..\DaneJSON.h"

#define ATRYBUT_PORT_SERWERA "portSerwera"
#define ATRYBUT_ADRES_SERWERA "adresSerwera"

namespace SpEx {

	KlientSideMulti::KlientSideMulti(const UstawieniaAplikacji& opcje)
		: BaseSide("KlientSideMulti")
	{
		ustawAdres(opcje[ATRYBUT_ADRES_SERWERA]);
		ustawPort(stoi(opcje[ATRYBUT_PORT_SERWERA], nullptr, 10));
		int error = socket();
		if (error != ERROR_SUCCESS) {
			ustawBlad(STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(Utils::pobierzDebugInfo()), STyp::Identyfikator(error), STyp::Tekst("B��d funkcji socket: "), STyp::Tekst("Klient::Klient() -> B��d funkcji socket: " + std::to_string(error))));
			ustawKodPowrotu(error);
			return;
		}
		funkcja_ = std::bind(&KlientSideMulti::pracujJakoKlient, this);
	}

	KlientSideMulti::KlientSideMulti(const std::string& ip, unsigned short port)
		: BaseSide("KlientSideMulti")
	{
		ustawAdres(ip);
		ustawPort(port);
		socket();
		funkcja_ = std::bind(&KlientSideMulti::pracujJakoKlient, this);
	}

	KlientSideMulti::KlientSideMulti(SOCKET socket, sockaddr_in & addr)
		: BaseSide("KlientSideMulti", socket, addr)
	{
	}

	std::future<bool> KlientSideMulti::dodajZadanie(std::shared_ptr<std::promise<bool> > zakonczenie, std::shared_ptr<const std::string> parametry, std::shared_ptr<std::string> rezultat, int flagi) {
		if (czyZakonczyc()) {
			zakonczenie->set_value(false);
			return zakonczenie->get_future();
		}
		std::lock_guard<std::mutex> lock(dostepDoZadan_);
		listaZadan_.emplace_back(std::make_shared<Zadanie>(zakonczenie, parametry, rezultat, flagi));
		return listaZadan_.back()->zakonczenie_->get_future();
	}


	void KlientSideMulti::pracujJakoKlient() {

		// ��czenie si� z serwerem
		int error = connect();
		if (error != ERROR_SUCCESS) {
			zakoncz();
			ustawBlad(STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(Utils::pobierzDebugInfo()), STyp::Identyfikator(error), STyp::Tekst("B��d funkcji connect: "), STyp::Tekst("Klient::pracujJakoKlient() -> B��d funkcji connect: " + std::to_string(error))));
			ustawKodPowrotu(error);
			return;
		}

		SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Ustanowiono po��czenie.");

		// P�tla wysy�aj�ca ��dania do serwera.
		while (!czyZakonczyc()) {
			std::shared_ptr<Zadanie> zadanie_ = nullptr;

			// Pobieranie ��dania
			{
				std::lock_guard<std::mutex> lock(dostepDoZadan_);
				if (listaZadan_.size()) {
					zadanie_ = listaZadan_.front();
					listaZadan_.pop_front();
				}
			}

			// Dzia�ania w przypadku braku oczekuj�cych ��da�.
			if (zadanie_ == nullptr) {
				switchToNonBlockingMode();
				auto rezultat = receive(nullptr, 0, 0);
				int er = WSAGetLastError();
				switchToBlockingMode();
				if (rezultat <= 0) {
					if (rezultat == 0) {
						if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Warning))
							SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Zamkni�to po��czenie: " + pobierzAdres());
						er = SOCK_CONNECTION_CLOSED;
					}
					else {
						if (WSAEWOULDBLOCK == er) {
							std::this_thread::sleep_for(std::chrono::milliseconds(100));
							continue;
						}
						else if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error))
							SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B��d po��cznie z serwerem: " + std::to_string(er));
					}
				}

				zakoncz();
				ustawKodPowrotu(er);
				break;
			}

			//Proces obs�ugi ��dania.
			DaneJSON dane(*this, *(zadanie_->zadanie_), *(zadanie_->rezultat_), zadanie_->flagi_);
			int error = RPC_OK;

			// Wysy�anie ��dania do serwera.
			error = dane.wyslij();
			if (error != RPC_OK) {
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Klient::pracujJakoKlient() -> B��d podczas wysy�ania danych: " + std::to_string(error));
				zakoncz();
				ustawKodPowrotu(error);
				zadanie_->zakonczenie_->set_value(false);
				break;
			}

			// Pr�ba odebrania wiadomo�ci zwrotniej
			error = dane.odbierz();
			if (error != RPC_OK) {
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Klient::pracujJakoKlient() -> B��d podczas odbierania danych: " + std::to_string(error));
				zakoncz();
				ustawKodPowrotu(error);
				zadanie_->zakonczenie_->set_value(false);
				break;
			}
			zadanie_->zakonczenie_->set_value(true);
		}

		{
			std::lock_guard<std::mutex> lock(dostepDoZadan_);
			for (auto &zadanie : listaZadan_)
				zadanie->zakonczenie_->set_value(false);
			listaZadan_.clear();
		}
		shutdown();
	}
}
