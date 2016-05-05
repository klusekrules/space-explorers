#include "Klient.h"
#include <vector>
#include <chrono>
#include "Kontroler\Aplikacja.h"
#include "RPC\StaleRPC.h"
#include <Ws2tcpip.h>
#include "TypyProste\Wyjatek.h"
#include "zlib.h"
#include "DaneJSON.h"
#include "Utils\Utils.h"

#define ROZMIAR_BUFORA 1024
#define ATRYBUT_PORT_SERWERA "portSerwera"
#define ATRYBUT_ADRES_SERWERA "adresSerwera"

#define IP_BUFOR_K_ROZMIAR 20

namespace SpEx{
	Klient::Klient(const UstawieniaAplikacji& opcje)
		: Watek("Klient", true), SocketBase(opcje)
	{
		ustawAdres(opcje[ATRYBUT_ADRES_SERWERA]);
		ustawPort(stoi(opcje[ATRYBUT_PORT_SERWERA], nullptr, 10));
		int error = socket();
		if (error != ERROR_SUCCESS) {
			ustawBlad(STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(Utils::pobierzDebugInfo()), STyp::Identyfikator(error), STyp::Tekst("B³¹d funkcji socket: "), STyp::Tekst("Klient::Klient() -> B³¹d funkcji socket: " + std::to_string(error))));
			ustawKodPowrotu(error);
			return;
		}
		funkcja_ = std::bind(&Klient::pracujJakoKlient, this);
	}

	Klient::Klient(const std::string& ip, unsigned short port)
		: Watek("Klient", true)
	{
		ustawAdres(ip);
		ustawPort(port);
		socket();
		funkcja_ = std::bind(&Klient::pracujJakoKlient, this);
	}

	Klient::Klient(SOCKET gniazdo, struct sockaddr_in &addr)
		: Watek("Klient", true) , SocketBase(gniazdo, addr)
	{
		funkcja_ = std::bind(&Klient::pracujJakoSerwer, this);
	}

	void Klient::wykonuj(){
		funkcja_();
	}

	bool Klient::czyAutoryzowany()const{
		return !hash_.empty();
	}

	void Klient::ustawKlucz(const std::string& hash){
		hash_ = hash;
	}

	void Klient::ustawAutoryzacje(const std::string& autoryzacja){
		autoryzacja_ = autoryzacja;
	}

	void Klient::ustawInstancje(const std::string& instancja){
		instancja_ = instancja;
	}

	const std::string& Klient::pobierzKlucz() const{
		return hash_;
	}

	std::future<bool> Klient::dodajZadanie(std::shared_ptr<std::promise<bool> > zakonczenie, std::shared_ptr<const std::string> parametry, std::shared_ptr<std::string> rezultat, int flagi){
		if (czyZakonczyc()){
			zakonczenie->set_value(false);
			return zakonczenie->get_future();
		}
		std::lock_guard<std::mutex> lock(dostepDoZadan_);
		listaZadan_.emplace_back(std::make_shared<Zadanie>(zakonczenie, parametry, rezultat, flagi));
		return listaZadan_.back()->zakonczenie_->get_future();
	}
	
	void Klient::pracujJakoKlient(){

		// £¹czenie siê z serwerem
		int error = connect();
		if (error != ERROR_SUCCESS){
			zakoncz();
			ustawBlad(STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(Utils::pobierzDebugInfo()), STyp::Identyfikator(error), STyp::Tekst("B³¹d funkcji connect: "), STyp::Tekst("Klient::pracujJakoKlient() -> B³¹d funkcji connect: " + std::to_string(error))));
			ustawKodPowrotu(error);
			return;
		}

		SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Ustanowiono po³¹czenie.");

		// Pêtla wysy³aj¹ca ¿¹dania do serwera.
		while (!czyZakonczyc()){
			std::shared_ptr<Zadanie> zadanie_ = nullptr;

			// Pobieranie ¿¹dania
			{
				std::lock_guard<std::mutex> lock(dostepDoZadan_);
				if (listaZadan_.size()){
					zadanie_ = listaZadan_.front();
					listaZadan_.pop_front();
				}
			}

			// Dzia³ania w przypadku braku oczekuj¹cych ¿¹dañ.
			if (zadanie_ == nullptr){
				switchToNonBlockingMode();
				auto rezultat = receive(nullptr, 0, 0);
				int er = WSAGetLastError();
				switchToBlockingMode();
				if (rezultat <= 0){
					if (rezultat == 0){
						if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Warning))
							SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Zamkniêto po³¹czenie: " + pobierzAdres());
						er = RPC_ERROR_CONNECTION_CLOSED;
					} else{
						if (WSAEWOULDBLOCK == er){
							std::this_thread::sleep_for(std::chrono::milliseconds(100));
							continue;
						} else if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error))
							SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d po³¹cznie z serwerem: " + std::to_string(er));
					}
				}

				zakoncz();
				ustawKodPowrotu(er);
				break;
			}

			//Proces obs³ugi ¿¹dania.
			DaneJSON dane(*this, *(zadanie_->zadanie_), *(zadanie_->rezultat_), zadanie_->flagi_);
			int error = RPC_OK;

			// Wysy³anie ¿¹dania do serwera.
			error = dane.wyslij();
			if (error != RPC_OK){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Klient::pracujJakoKlient() -> B³¹d podczas wysy³ania danych: " + std::to_string(error));
				zakoncz();
				ustawKodPowrotu(error);
				zadanie_->zakonczenie_->set_value(false);
				break;
			}

			// Próba odebrania wiadomoœci zwrotniej
			error = dane.odbierz();
			if (error != RPC_OK){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Klient::pracujJakoKlient() -> B³¹d podczas odbierania danych: " + std::to_string(error));
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
	
	const std::atomic<bool>& Klient::czyCzekaNaZakonczenie() const{
		return czyZakonczyc();
	}
	
	void Klient::pracujJakoSerwer(){
		while (!czyZakonczyc()){
			DaneJSON dane(*this);
			int error = dane.odbierz();
			if (error != RPC_OK){
				if (error != RPC_ERROR_CONNECTION_CLOSED)
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Klient::pracujJakoSerwer() -> B³¹d podczas odbierania danych: " + std::to_string(error));
				break;
			}

			error = dane.wykonajMetode();
			if (error != RPC_OK){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Klient::pracujJakoSerwer() -> B³¹d podczas przetwarzania danych: " + std::to_string(error));
			}

			error = dane.wyslij();
			if (error != RPC_OK){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Klient::pracujJakoSerwer() -> B³¹d podczas wysy³ania danych: " + std::to_string(error));
				break;
			}
		}
		shutdown();
	}
	
	void Klient::autoryzujMetode(std::string& instancja, std::string& autoryzacja) const{
		instancja = instancja_;
		autoryzacja = autoryzacja_;
	}
	
	int Klient::odbierz(char *dane, int dlugosc, int flagi) const{
		return receive(dane, dlugosc, flagi);
	}

	int Klient::wyslij(const char * dane, int dlugosc, int flagi) const{
		return send(dane, dlugosc, flagi);
	}

	Klient::~Klient(){
		shutdown();
	}
}
