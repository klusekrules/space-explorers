#include "GniazdoWinSock.h"

int SpEx::GniazdoWinSock::wyslij(const char * dane, int rozmiar, int flagi) {
	int retVal = 0;
	while (rozmiar > 0 && sprawdzWarunek()) {
		retVal = SendData(dane, rozmiar, flagi);
		if (retVal == SOCKET_ERROR) {
			retVal = WSAGetLastError();
			if (retVal == WSAEWOULDBLOCK) {
				continue;
			}
			return retVal;
		}
		dane += retVal;
		rozmiar -= retVal;
	}
	return sprawdzWarunek() ? ERROR_SUCCESS : SOCK_PROCCESSING_BREAK;
}

int SpEx::GniazdoWinSock::odbierz(char * dane, int rozmiar, int flagi) {
	while (rozmiar > 0 && sprawdzWarunek()) {
		int retVal = RecvData(dane, rozmiar, flagi);
		if (retVal == SOCKET_ERROR) {
			retVal = WSAGetLastError();
			if (retVal == WSAEWOULDBLOCK) {
				continue;
			}
			return retVal;
		}
		else if (retVal == 0) {
			return SOCK_CONNECTION_CLOSED;
		}
		dane += retVal;
		rozmiar -= retVal;
	}
	return sprawdzWarunek() ? ERROR_SUCCESS : SOCK_PROCCESSING_BREAK;
}

void SpEx::GniazdoWinSock::ustawWarunekOczekiwania(std::function<bool(void)> warunek){
		warunek_ = warunek;
}

SpEx::GniazdoWinSock::GniazdoWinSock(SocketBase & gniazdo)
	: gniazdo_(gniazdo) 
{
}
