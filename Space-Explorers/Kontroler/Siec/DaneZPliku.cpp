#include "DaneZPliku.h"
#include <Ws2tcpip.h>
#include "GniazdoWinSock.h"
#include "RPC\StaleRPC.h"

#include "Kompresja.h"
#include "Szyfrowanie.h"
#include <zlib.h>

#include "Utils\Utils.h"

SpEx::DaneZPliku::DaneZPliku(Klient& ref,const std::string & adresPliku)
	: ref_(ref), plik_ (nullptr)
{
	if (!adresPliku.empty()) {
		SpEx::Utils::tworzSciezke(adresPliku);
		plik_ = fopen(adresPliku.c_str(),"ab+");
		adresPliku_ = adresPliku;
	}
}

SpEx::DaneZPliku::~DaneZPliku(){
	if (plik_ != nullptr)
		fclose(plik_);
}

unsigned __int64 SpEx::DaneZPliku::rozmiar() const{
	return rozmiar_;
}

int SpEx::DaneZPliku::przygotujDane(){
	if ((flagi_ & 0xFFFFFFFF00000000) >> 32 != FLAGA_WERSJA)
		return SOCK_PROTOCOL_MISMATCH;
	if (received_) {
		fseek(plik_, 0, SEEK_SET);
		char buffer[L_tmpnam];
		if (flagi_ & FLAGA_SZYFROWANIE) {
			tmpnam(buffer);
			FILE* out = fopen(buffer, "ab+");
			Szyfrowanie szyfr(ref_.pobierzKlucz(),plik_,out);
			int ret = szyfr.deszyfrowanie(); 
			if (ret != ERROR_SUCCESS) {
				fclose(out);
				remove(buffer);
				return ret;
			}
			fclose(plik_);
			remove(adresPliku_.c_str());
			rename(buffer, adresPliku_.c_str());
			plik_ = out;
			fseek(plik_,0,SEEK_SET);
		}

		if (flagi_ & FLAGA_KOMPRESJA) {
			tmpnam(buffer);
			FILE* out = fopen(buffer, "ab+");
			Kompresja dane(plik_, out);
			int ret = dane.dekompresja();
			if (ret != ERROR_SUCCESS) {
				fclose(out);
				remove(buffer);
				return ret;
			}
			fclose(plik_);
			remove(adresPliku_.c_str());
			rename(buffer, adresPliku_.c_str());
			plik_ = out;
			fseek(plik_, 0, SEEK_SET);
		}
	} else {
		fseek(plik_, 0, SEEK_SET);

		if (flagi_ & FLAGA_KOMPRESJA) {
			FILE* out = tmpfile();
			Kompresja dane(plik_, out);
			int ret = dane.kompresja();
			if (ret != ERROR_SUCCESS) {
				fclose(out);
				return ret;
			}
			fclose(plik_);
			plik_ = out;
			fseek(plik_,0,SEEK_SET);
		}

		if (flagi_ & FLAGA_SZYFROWANIE) {
			FILE* out = tmpfile();
			Szyfrowanie szyfr(ref_.pobierzKlucz(), plik_, out);
			int ret = szyfr.szyfrowanie();
			if (ret != ERROR_SUCCESS) {
				fclose(out);
				return ret;
			}
			fclose(plik_);
			plik_ = out;
			fseek(plik_, 0, SEEK_SET);
		}

	}
	return ERROR_SUCCESS;
}

int SpEx::DaneZPliku::wyslij(GniazdoWinSock & e, int flagi){
	if (plik_ == nullptr) {
		return EOF;
	}
	received_ = false;
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
	received_ = true;
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
