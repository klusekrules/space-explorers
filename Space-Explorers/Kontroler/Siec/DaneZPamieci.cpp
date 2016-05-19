#include "DaneZPamieci.h"
#include <Ws2tcpip.h>
#include "GniazdoWinSock.h"
#include "RPC\StaleRPC.h"

#include "Kompresja.h"
#include "Szyfrowanie.h"

SpEx::DaneZPamieci::DaneZPamieci(Klient & ref, const std::string& dane)
	:ref_(ref),buffor_(dane)
{
}

SpEx::DaneZPamieci::DaneZPamieci(Klient & ref, std::string&& dane)
	: ref_(ref), buffor_(std::move(dane))
{
}

SpEx::DaneZPamieci::DaneZPamieci(Klient & ref)
	: ref_(ref)
{
}

unsigned __int64 SpEx::DaneZPamieci::rozmiar() const{
	return buffor_.size();
}

int SpEx::DaneZPamieci::przygotujDane(){
	if ((flagi_ & 0xFFFFFFFF00000000) >> 32 != FLAGA_WERSJA)
		return SOCK_PROTOCOL_MISMATCH;
	if (received_) {		
		if (flagi_ & FLAGA_SZYFROWANIE) {
			Szyfrowanie szyfr(ref_.pobierzKlucz(),buffor_);
			int ret = szyfr.deszyfrowanie();
			if (ret != ERROR_SUCCESS) {
				return ret;
			}
		}
		if (flagi_ & FLAGA_KOMPRESJA) {
			std::string out;
			Kompresja dane(buffor_, out);
			int ret = dane.dekompresja();
			if (ret != ERROR_SUCCESS) {
				return ret;
			}
			buffor_ = std::move(out);
		}
	} else {
		if (flagi_ & FLAGA_KOMPRESJA) {
			std::string out;
			Kompresja dane(buffor_, out);
			int ret = dane.kompresja();
			if (ret != ERROR_SUCCESS) {
				return ret;
			}
			buffor_ = std::move(out);
		}
		if (flagi_ & FLAGA_SZYFROWANIE) {
			Szyfrowanie szyfr(ref_.pobierzKlucz(), buffor_);
			int ret = szyfr.szyfrowanie();
			if (ret != ERROR_SUCCESS) {
				return ret;
			}
		}
	}
	return ERROR_SUCCESS;
}

const std::string& SpEx::DaneZPamieci::pobierzBufor() const
{
	return buffor_;
}

int SpEx::DaneZPamieci::wyslij(GniazdoWinSock & e, int flagi){
	if (buffor_.size() == 0) {
		return EOF;
	}
	received_ = false;
	long fsize = htonl(buffor_.size());
	int error;
	if (error = e.wyslij((char*)&fsize, sizeof(fsize), flagi))
		return error;
	if (error = e.wyslij(&buffor_[0], buffor_.size(), flagi))
		return error;		
	return e.sprawdzWarunek() ? ERROR_SUCCESS : SOCK_PROCCESSING_BREAK;
}

int SpEx::DaneZPamieci::odbierz(GniazdoWinSock & e, int flagi){
	long size;
	int error;
	received_ = true;
	if (error = e.odbierz((char*)&size, sizeof(size), flagi))
		return error;
	size = ntohl(size);
	buffor_.resize(size);
	if (error = e.odbierz(&buffor_[0], buffor_.size(), flagi))
		return error;
	return e.sprawdzWarunek() ? ERROR_SUCCESS : SOCK_PROCCESSING_BREAK;
}

