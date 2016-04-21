#include "Nasluchiwacz.h"
#include <Ws2tcpip.h>
#include <thread>
#include "Utils\Utils.h"

#define ATRYBUT_PORT_SERWERA "portSerwera"
#define IP_BUFOR_K_ROZMIAR 20

SpEx::Nasluchiwacz::Nasluchiwacz()
	: SocketBase(), Watek(true)
{
	init();
}

SpEx::Nasluchiwacz::Nasluchiwacz(const UstawieniaAplikacji & opcje)
	: SocketBase(opcje) ,Watek(true)
{
	init();
}

void SpEx::Nasluchiwacz::wykonuj(){
	int error = 0;

	struct sockaddr_in addr;
	SOCKET gniazdoKlienta = INVALID_SOCKET;

	SLog::Log::pobierzInstancje().loguj(SLog::Log::Info,"Rozpocz�to nas�uchiwanie.");

	while (!czyZakonczyc()) {
		error = accept(gniazdoKlienta,addr);
		//TODO: Lepsza obs�uga b��d�w. Cz�� b��d�w nie powinna przerywa� dzia�ania p�tli.
		if (error != WSAEWOULDBLOCK && gniazdoKlienta == INVALID_SOCKET) {
			ustawBlad(STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(Utils::pobierzDebugInfo()), STyp::Identyfikator(error), STyp::Tekst("B��d odbierania po��czenia"), STyp::Tekst("B��d funkcji accept: " + std::to_string(error))));
			ustawKodPowrotu(error);
			break;
		}

		if (gniazdoKlienta != INVALID_SOCKET) {
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Przychodz�ce po��czenie od: " + std::string(translateIP(addr)));
			if (!polaczeniePrzychodzace(gniazdoKlienta, addr))
				break;
		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}
	SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Zako�czono nas�uchiwanie.");

}

void SpEx::Nasluchiwacz::init(){
	//ToDo: Zaimplementowa� szablon obs�uguj�cy b��d. Jeden og�lny drugi, cz�ciowo zainicjalizowany.
	int error = 0;

	error = socket();
	if (error != ERROR_SUCCESS) {
		ustawBlad(STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(Utils::pobierzDebugInfo()), STyp::Identyfikator(error), STyp::Tekst("B��d inicjalizacji gniazda."), STyp::Tekst("B��d funkcji socket: " + std::to_string(error))));
		ustawKodPowrotu(error);
		return;
	}

	error = bind();
	if (error != ERROR_SUCCESS) {
		ustawBlad(STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(Utils::pobierzDebugInfo()), STyp::Identyfikator(error), STyp::Tekst("B��d inicjalizacji gniazda."), STyp::Tekst("B��d funkcji bind: " + std::to_string(error))));
		ustawKodPowrotu(error);
		return;
	}

	error = listen();
	if (error != ERROR_SUCCESS) {
		ustawBlad(STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(Utils::pobierzDebugInfo()), STyp::Identyfikator(error), STyp::Tekst("B��d inicjalizacji gniazda."), STyp::Tekst("B��d funkcji listen: " + std::to_string(error))));
		ustawKodPowrotu(error);
		return;
	}

	if (port_ == 0) {
		error = portUpdate();
		if (error != ERROR_SUCCESS) {
			ustawBlad(STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(Utils::pobierzDebugInfo()), STyp::Identyfikator(error), STyp::Tekst("B��d inicjalizacji gniazda."), STyp::Tekst("B��d funkcji portUpdate: " + std::to_string(error))));
			ustawKodPowrotu(error);
			return;
		}
	}

	error = switchToNonBlockingMode();
	if (error != ERROR_SUCCESS) {
		ustawBlad(STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(Utils::pobierzDebugInfo()), STyp::Identyfikator(error), STyp::Tekst("B��d inicjalizacji gniazda."), STyp::Tekst("B��d funkcji switchToNonBlockingMode: " + std::to_string(error))));
		ustawKodPowrotu(error);
		return;
	}
}

SpEx::Nasluchiwacz::~Nasluchiwacz(){
	shutdown();
}
