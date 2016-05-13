#include "DaneZPliku.h"
#include <Ws2tcpip.h>
#include "GniazdoWinSock.h"
#include "RPC\StaleRPC.h"

SpEx::DaneZPliku::DaneZPliku(const std::string & adresPliku)
	: plik_ (nullptr)
{
	if (!adresPliku.empty()) {
		fopen(adresPliku.c_str(),"rw");
	}
}

SpEx::DaneZPliku::~DaneZPliku(){
	if (plik_ != nullptr)
		fclose(plik_);
}

unsigned __int64 SpEx::DaneZPliku::rozmiar() const{
	return rozmiar_;
}

int SpEx::DaneZPliku::wyslij(GniazdoWinSock & e, int flagi){
	if (plik_ == nullptr) {
		return EOF;
	}

	fseek(plik_, 0, SEEK_END);
	long filesize = ftell(plik_);
	rewind(plik_);

	if (filesize == EOF) {
		return EOF;
	}

	long fsize = htonl(filesize);
	int error;
	if (! (error = SendData(e, (char*)&fsize, sizeof(fsize), flagi)))
		return error;
	if (filesize > 0) {
		char buffer[ROZMIAR_BUFFORA];
		do {
			size_t num = min(filesize, sizeof(buffer));
			num = fread(buffer, 1, num, plik_);
			if (num < 1) {
				return EOF;
			}
			if (!(error = SendData(e, buffer, num, flagi)))
				return error;
			filesize -= num;
		} while (filesize > 0 && e.sprawdzWarunek());
	}
	return e.sprawdzWarunek() ? ERROR_SUCCESS : SOCK_PROCCESSING_BREAK;
}

int SpEx::DaneZPliku::odbierz(GniazdoWinSock & e, int flagi){
	long filesize;
	int error;
	if (!(error = RecvData(e,(char*)&filesize, sizeof(filesize), flagi)))
		return error;
	filesize = ntohl(filesize);
	if (filesize > 0) {
		char buffer[ROZMIAR_BUFFORA];
		do {
			int num = min(filesize, sizeof(buffer));
			if (!(error = RecvData(e, buffer, num, flagi)))
				return error;
			int offset = 0;
			do {
				size_t written = fwrite(&buffer[offset], sizeof(char), num - offset, plik_);
				if (written == 0) {
					return ferror(plik_);
				}
				offset += written;
			} while (offset < num && e.sprawdzWarunek());
			filesize -= num;
		} while (filesize > 0 && e.sprawdzWarunek());
	}
	return e.sprawdzWarunek() ? ERROR_SUCCESS : SOCK_PROCCESSING_BREAK;
}
