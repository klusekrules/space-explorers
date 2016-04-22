#include "SerwerRaw.h"
#include <Ws2tcpip.h>

#ifndef LOG_OFF_ALL
#include "Logger\Log.h"
#endif

namespace SpEx {
	SerwerRaw::SerwerRaw(const std::string& nazwaPliku, FILE* fp)
		: Nasluchiwacz(), fp_(fp), nazwaPliku_(nazwaPliku)
	{
#ifndef LOG_OFF_ALL
		if (fp_ == nullptr) {
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Brak pliku!");
			return;
		}
#endif
	}

	bool SerwerRaw::SendData(SOCKET sock, void *buf, int buflen) {
		char *pbuf = (char *)buf; 
		int num = 0;
		while (buflen > 0) {
			num = ::send(sock, pbuf, buflen, 0);
			if (num == SOCKET_ERROR) {
				int error = WSAGetLastError();
				if (error == WSAEWOULDBLOCK) {
					continue;
				}
				error_ = error;
				return false;
			}
			pbuf += num;
			buflen -= num;
		}
		return true;
	}
	
	bool SerwerRaw::SendFile(SOCKET sock) {
		if (fp_ == nullptr) {
			error_ = EOF;
			return false;
		}

		fseek(fp_, 0, SEEK_END);
		long filesize = ftell(fp_);
		rewind(fp_);

		if (filesize == EOF) {
			error_ = EOF;
			return false;
		}

		long fsize = htonl(filesize);
		if(!SendData(sock,&fsize, sizeof(fsize)))
			return false;
		if (filesize > 0){
			char buffer[1024];
			do{
				size_t num = min(filesize, sizeof(buffer));
				num = fread(buffer, 1, num, fp_);
				if (num < 1) {
					error_ = 0;
					return false;
				}
				if (!SendData(sock,buffer, num))
					return false;
				filesize -= num;
			} while (filesize > 0);
		}
		return true;
	}

	bool SerwerRaw::polaczeniePrzychodzace(SOCKET gniazdo, sockaddr_in &){
#ifndef LOG_OFF_ALL
		if (!SendFile(gniazdo)) {
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d wysy³ania pliku: " + std::to_string(error_));
		} else {
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Wys³ano plik: " + nazwaPliku_);
		}
#else
		SendFile(gniazdo);
#endif
		::shutdown(gniazdo, SD_SEND);
		closesocket(gniazdo);
		zakoncz();
		return false;
	}

	SerwerRaw::~SerwerRaw(){
		if (fp_ != nullptr) {
			fclose(fp_);
		}
	}
}
