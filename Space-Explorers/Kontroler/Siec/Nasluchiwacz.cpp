#include "Nasluchiwacz.h"
#include <Ws2tcpip.h>
#include <thread>
#include "Utils\Utils.h"

#define ATRYBUT_PORT_SERWERA "portSerwera"
#define IP_BUFOR_K_ROZMIAR 20

SpEx::Nasluchiwacz::Nasluchiwacz(const UstawieniaAplikacji & opcje)
	: SocketBase(opcje) ,Watek(true)
{
}

void SpEx::Nasluchiwacz::wykonuj(){
	//ToDo: Zaimplementowaæ szablon obs³uguj¹cy b³¹d. Jeden ogólny drugi, czêœciowo zainicjalizowany.
	int error = 0;

	error = socket();
	if (error != ERROR_SUCCESS) {
		ustawBlad(STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(Utils::pobierzDebugInfo()),STyp::Identyfikator(error), STyp::Tekst("B³¹d inicjalizacji gniazda."), STyp::Tekst("B³¹d funkcji socket: " + std::to_string(error))));
		ustawKodPowrotu(error);
		return;
	}

	error = bind();
	if (error != ERROR_SUCCESS) {
		ustawBlad(STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(Utils::pobierzDebugInfo()), STyp::Identyfikator(error), STyp::Tekst("B³¹d inicjalizacji gniazda."), STyp::Tekst("B³¹d funkcji bind: " + std::to_string(error))));
		ustawKodPowrotu(error);
		return;
	}

	error = listen();
	if (error != ERROR_SUCCESS) {
		ustawBlad(STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(Utils::pobierzDebugInfo()), STyp::Identyfikator(error), STyp::Tekst("B³¹d inicjalizacji gniazda."), STyp::Tekst("B³¹d funkcji listen: " + std::to_string(error))));
		ustawKodPowrotu(error);
		return;
	}

	if (port_ == 0) {
		error = portUpdate();
		if (error != ERROR_SUCCESS) {
			ustawBlad(STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(Utils::pobierzDebugInfo()), STyp::Identyfikator(error), STyp::Tekst("B³¹d inicjalizacji gniazda."), STyp::Tekst("B³¹d funkcji portUpdate: " + std::to_string(error))));
			ustawKodPowrotu(error);
			return;
		}
	}

	error = switchToNonBlockingMode();
	if (error != ERROR_SUCCESS) {
		ustawBlad(STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(Utils::pobierzDebugInfo()), STyp::Identyfikator(error), STyp::Tekst("B³¹d inicjalizacji gniazda."), STyp::Tekst("B³¹d funkcji switchToNonBlockingMode: " + std::to_string(error))));
		ustawKodPowrotu(error);
		return;
	}

	struct sockaddr_in addr;
	SOCKET gniazdoKlienta = INVALID_SOCKET;

	SLog::Log::pobierzInstancje().loguj(SLog::Log::Info,"Rozpoczêto nas³uchiwanie.");

	while (!czyZakonczyc()) {
		error = accept(gniazdoKlienta,addr);
		//TODO: Lepsza obs³uga b³êdów. Czêœæ b³êdów nie powinna przerywaæ dzia³ania pêtli.
		if (error != WSAEWOULDBLOCK && gniazdoKlienta == INVALID_SOCKET) {
			ustawBlad(STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(Utils::pobierzDebugInfo()), STyp::Identyfikator(error), STyp::Tekst("B³¹d odbierania po³¹czenia"), STyp::Tekst("B³¹d funkcji accept: " + std::to_string(error))));
			ustawKodPowrotu(error);
			break;
		}

		if (gniazdoKlienta != INVALID_SOCKET) {
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Przychodz¹ce po³¹czenie od: " + std::string(translateIP(addr)));
			if (!polaczeniePrzychodzace(gniazdoKlienta, addr))
				break;
		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}

}

SpEx::Nasluchiwacz::~Nasluchiwacz(){
	shutdown();
}
