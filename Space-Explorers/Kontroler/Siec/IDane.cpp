#include "IDane.h"
#include <WS2tcpip.h>
#include "RPC\StaleRPC.h"
#include "GniazdoWinSock.h"

namespace SpEx {
	int IDane::SendData(GniazdoWinSock& e, char* buf, int buflen, int flagi) {
		char *pbuf = (char *)buf;
		int num = 0;
		while (buflen > 0 && e.sprawdzWarunek()) {
			num = e.wyslij(buf, buflen, flagi);
			if (num == SOCKET_ERROR) {
				int error = WSAGetLastError();
				if (error == WSAEWOULDBLOCK) {
					continue;
				}
				return error;
			}
			pbuf += num;
			buflen -= num;
		}
		return e.sprawdzWarunek() ? ERROR_SUCCESS : SOCK_PROCCESSING_BREAK;
	}

	int IDane::RecvData(GniazdoWinSock& e, char* buf, int buflen, int flagi) {
		while (buflen > 0 && e.sprawdzWarunek()) {
			int num = e.odbierz(buf, buflen, flagi);
			if (num == SOCKET_ERROR) {
				int error = WSAGetLastError();
				if (error == WSAEWOULDBLOCK) {
					continue;
				}
				return error;
			}
			else if (num == 0) {
				return SOCK_CONNECTION_CLOSED;
			}
			buf += num;
			buflen -= num;
		}
		return e.sprawdzWarunek() ? ERROR_SUCCESS : SOCK_PROCCESSING_BREAK;
	}
}