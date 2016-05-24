#include "BaseSide.h"
#include <vector>
#include <chrono>
#include "Kontroler\Aplikacja.h"
#include "..\RPC\StaleRPC.h"
#include <Ws2tcpip.h>
#include "TypyProste\Wyjatek.h"
#include "zlib.h"
#include "..\DaneJSON.h"
#include "Utils\Utils.h"

#define ROZMIAR_BUFORA 1024

#define IP_BUFOR_K_ROZMIAR 20

namespace SpEx{
	
	void BaseSide::wykonuj(){
		funkcja_();
	}

	bool BaseSide::czyAutoryzowany()const{
		return !hash_.empty();
	}

	void BaseSide::ustawKlucz(const std::string& hash){
		hash_ = hash;
	}

	void BaseSide::ustawAutoryzacje(const std::string& autoryzacja){
		autoryzacja_ = autoryzacja;
	}

	void BaseSide::ustawInstancje(const std::string& instancja){
		instancja_ = instancja;
	}

	const std::string& BaseSide::pobierzKlucz() const{
		return hash_;
	}
	
	const std::atomic<bool>& BaseSide::czyCzekaNaZakonczenie() const{
		return czyZakonczyc();
	}
	
	
	void BaseSide::autoryzujMetode(std::string& instancja, std::string& autoryzacja) const{
		instancja = instancja_;
		autoryzacja = autoryzacja_;
	}

	BaseSide::~BaseSide(){
		shutdown();
	}

	BaseSide::BaseSide(std::string nazwa)
		: Watek(nazwa, true), SocketBase()
	{
	}

	BaseSide::BaseSide(std::string nazwa, SOCKET socket, sockaddr_in & addr)
		: Watek(nazwa, true), SocketBase(socket,addr)
	{
	}
}
