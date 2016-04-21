#include "SerwerRaw.h"
#include "Logger\Log.h"
#include <Ws2tcpip.h>

namespace SpEx {
	SerwerRaw::SerwerRaw(const std::string& nazwaPliku, FILE* fp)
		: Nasluchiwacz(), fp_(fp), nazwaPliku_(nazwaPliku)
	{
		if (fp_ == nullptr) {
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Brak pliku!");
			return;
		}
	}

	bool SerwerRaw::SendData(SOCKET sock, void *buf, int buflen) {
		char *pbuf = (char *)buf;
		while (buflen > 0) {
			int num = ::send(sock, pbuf, buflen, 0);
			if (num == SOCKET_ERROR) {				
				auto ret = WSAGetLastError();
				if (ret == WSAEWOULDBLOCK) {
					continue;
				}
				return false;
			}
			pbuf += num;
			buflen -= num;
		}
		return true;
	}
	
	bool SerwerRaw::SendFile(SOCKET sock) {
		fseek(fp_, 0, SEEK_END);
		long filesize = ftell(fp_);
		rewind(fp_);
		if (filesize == EOF)
			return false;
		long fsize = htonl(filesize);
		if(!SendData(sock,&fsize, sizeof(fsize)))
			return false;
		if (filesize > 0){
			char buffer[1024];
			do{
				size_t num = min(filesize, sizeof(buffer));
				num = fread(buffer, 1, num, fp_);
				if (num < 1)
					return false;
				if (!SendData(sock,buffer, num))
					return false;
				filesize -= num;
			} while (filesize > 0);
		}
		return true;
	}

	bool SerwerRaw::polaczeniePrzychodzace(SOCKET gniazdo, sockaddr_in &)
	{
		if (!SendFile(gniazdo)) {
			auto error = WSAGetLastError();
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d wysy³ania pliku: " + std::to_string(error));
		}

		SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Wys³ano plik: " + nazwaPliku_);
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
