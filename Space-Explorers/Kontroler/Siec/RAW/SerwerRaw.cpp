#include "SerwerRaw.h"
#include "Logger\Log.h"
#include <Ws2tcpip.h>

namespace SpEx {
	SerwerRaw::SerwerRaw(const std::string& nazwaPliku, FILE* fp)
		: Watek(true), fp_(fp), nazwaPliku_(nazwaPliku), gniazdo_(INVALID_SOCKET), port_(0)
	{
		if (fp_ == nullptr) {
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Brak pliku!");
			return;
		}
		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = 0;
		addr.sin_addr.s_addr = INADDR_ANY;
		gniazdo_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		if (INVALID_SOCKET == gniazdo_) {
			auto error = WSAGetLastError();
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji socket: " + std::to_string(error));
		}

		if (SOCKET_ERROR == bind(gniazdo_, (struct sockaddr*) &addr, sizeof(addr))) {
			auto error = WSAGetLastError();
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji bind: " + std::to_string(error));
		}

		if (SOCKET_ERROR == listen(gniazdo_, SOMAXCONN)) {
			auto error = WSAGetLastError();
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji listen: " + std::to_string(error));
			return;
		}
		struct sockaddr_in sin;
		socklen_t len = sizeof(sin);
		if (SOCKET_ERROR == getsockname(gniazdo_, (struct sockaddr *)&sin, &len)) {
			auto error = WSAGetLastError();
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji getsockname: " + std::to_string(error));
		}
		else
			port_ = ntohs(sin.sin_port);

	}

	u_short SerwerRaw::getPort() const{
		return port_;
	}

	bool SerwerRaw::SendData(SOCKET sock, void *buf, int buflen) const {
		char *pbuf = (char *)buf;
		while (buflen > 0) {
			int num = send(sock, pbuf, buflen, 0);
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
	
	bool SerwerRaw::SendFile(SOCKET sock) const {
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

	void SerwerRaw::wykonuj() {
		if (fp_ == nullptr) {
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Brak pliku!");
			return;
		}

		struct sockaddr_in addr;
		int addrSize = sizeof(addr);
		SOCKET gniazdoKlienta = INVALID_SOCKET;
		u_long iMode = 1; //Nonblock
		int nError = 0;
		ioctlsocket(gniazdo_, FIONBIO, &iMode);

		while (!czyZakonczyc()) {
			gniazdoKlienta = accept(gniazdo_, (struct sockaddr*) &addr, &addrSize);
			nError = WSAGetLastError();
			if (nError != WSAEWOULDBLOCK && gniazdoKlienta == INVALID_SOCKET) {
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d funkcji listen: " + std::to_string(nError));
				break;
			}
			if (gniazdoKlienta != INVALID_SOCKET) {
				if (!SendFile(gniazdoKlienta)) {
					auto error = WSAGetLastError();
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d wysy³ania pliku: " + std::to_string(error));
				}
				shutdown(gniazdoKlienta, SD_SEND);
				closesocket(gniazdoKlienta);
				zakoncz();
			}
			else {
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
		}
		
	}

	SerwerRaw::~SerwerRaw()
	{
		if (fp_ != nullptr) {
			fclose(fp_);
		}
		if (gniazdo_ != INVALID_SOCKET) {
			shutdown(gniazdo_, SD_SEND);
			closesocket(gniazdo_);
		}
	}
}
