#include "Klient.h"
#include <vector>
#include <chrono>
#include "Kontroler\Aplikacja.h"
#include "RPC\StaleRPC.h"
#include <Ws2tcpip.h>
#include "TypyProste\Wyjatek.h"
#include "zlib.h"
#include "DaneTCP.h"

#define ROZMIAR_BUFORA 1024
#define ATRYBUT_PORT_SERWERA "portSerwera"
#define ATRYBUT_ADRES_SERWERA "adresSerwera"


namespace SpEx{
	Klient::Klient(const UstawieniaAplikacji& opcje)
		: Watek(true)
	{

		struct addrinfo *result = NULL;
		if (getaddrinfo(opcje[ATRYBUT_ADRES_SERWERA].c_str(), nullptr, nullptr, &result)){
			throw STyp::Wyjatek(EXCEPTION_PLACE,Aplikacja::pobierzInstancje().pobierzSladStosu());
		}
		decltype(addr_) &sock = *((decltype(addr_)*)(result->ai_addr));
		addr_.sin_family = AF_INET;
		addr_.sin_port = htons(stoi(opcje[ATRYBUT_PORT_SERWERA], nullptr, 10));
		addr_.sin_addr.s_addr = sock.sin_addr.s_addr;
		gniazdo_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		funkcja_ = std::bind(&Klient::pracujJakoKlient, this);
	}

	Klient::Klient(const std::string& ip, unsigned short port)
		: Watek(true)
	{

		struct addrinfo *result = NULL;
		if (getaddrinfo(ip.c_str(), nullptr, nullptr, &result)){
			throw STyp::Wyjatek(EXCEPTION_PLACE, Aplikacja::pobierzInstancje().pobierzSladStosu());
		}
		decltype(addr_) &sock = *((decltype(addr_)*)(result->ai_addr));
		addr_.sin_family = AF_INET;
		addr_.sin_port = htons(port);
		addr_.sin_addr.s_addr = sock.sin_addr.s_addr;
		gniazdo_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		funkcja_ = std::bind(&Klient::pracujJakoKlient, this);
	}

	Klient::Klient(SOCKET gniazdo, struct sockaddr_in &addr)
		: Watek(true)
	{
		gniazdo_ = gniazdo;
		addr_ = addr;
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
		if (SOCKET_ERROR == connect(gniazdo_, (struct sockaddr*) &addr_, sizeof(addr_))){
			auto error = WSAGetLastError();
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Klient::pracujJakoKlient() -> B³¹d funkcji connect: " + std::to_string(error));
			zakoncz();
			return;
		}

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
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				continue;
			}

			//Proces obs³ugi ¿¹dania.
			DaneTCP dane(*this, *(zadanie_->zadanie_), *(zadanie_->rezultat_), zadanie_->flagi_);
			int error = RPC_OK;

			// Wysy³anie ¿¹dania do serwera.
			error = dane.wyslij();
			if (error != RPC_OK){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Klient::pracujJakoKlient() -> B³¹d podczas wysy³ania danych: " + std::to_string(error));
				zakoncz();
				zadanie_->zakonczenie_->set_value(false);
				break;
			}

			// Próba odebrania wiadomoœci zwrotniej
			error = dane.odbierz();
			if (error != RPC_OK){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Klient::pracujJakoKlient() -> B³¹d podczas odbierania danych: " + std::to_string(error));
				zakoncz();
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
		zamknijPolaczenie();		
	}
	
	int Klient::odbierz(char* bufor, int rozmiar, int flagi) const{
		return recv(gniazdo_, bufor, rozmiar, flagi);
	}

	int Klient::wyslij(const char* wiadomosc, int dlugosc, int flagi) const{
		return send(gniazdo_, wiadomosc, dlugosc, flagi);
	}

	const std::atomic<bool>& Klient::czyCzekaNaZakonczenie() const{
		return czyZakonczyc();
	}

	void Klient::pracujJakoSerwer(){
		while (!czyZakonczyc()){
			DaneTCP dane(*this);
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
		zamknijPolaczenie();
	}
	
	void Klient::autoryzujMetode(std::string& instancja, std::string& autoryzacja) const{
		instancja = instancja_;
		autoryzacja = autoryzacja_;
	}

	void Klient::zamknijPolaczenie(){
		if (gniazdo_ != INVALID_SOCKET){
			shutdown(gniazdo_, SD_SEND);
			closesocket(gniazdo_);
			gniazdo_ = INVALID_SOCKET;
		}
	}

	Klient::~Klient()
	{
		zamknijPolaczenie();
	}
}
