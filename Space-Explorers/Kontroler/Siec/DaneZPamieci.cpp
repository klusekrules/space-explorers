#include "DaneZPamieci.h"
#include <Ws2tcpip.h>
#include "GniazdoWinSock.h"
#include "RPC\StaleRPC.h"

unsigned __int64 SpEx::DaneZPamieci::rozmiar() const{
	return buffor_.size();
}

int SpEx::DaneZPamieci::wyslij(GniazdoWinSock & e, int flagi){
	if (buffor_.size() == 0) {
		return EOF;
	}

	long fsize = htonl(buffor_.size());
	int error;
	if (!(error = SendData(e, (char*)&fsize, sizeof(fsize), flagi)))
		return error;
	if (!(error = SendData(e, buffor_.data(), buffor_.size(), flagi)))
		return error;		
	return e.sprawdzWarunek() ? ERROR_SUCCESS : SOCK_PROCCESSING_BREAK;
}

int SpEx::DaneZPamieci::odbierz(GniazdoWinSock & e, int flagi){
	long size;
	int error;
	if (!(error = RecvData(e, (char*)&size, sizeof(size), flagi)))
		return error;
	size = ntohl(size);
	buffor_.resize(size);
	if (!(error = RecvData(e, buffor_.data(), buffor_.size(), flagi)))
		return error;
	return e.sprawdzWarunek() ? ERROR_SUCCESS : SOCK_PROCCESSING_BREAK;
}

