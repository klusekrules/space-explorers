#include "KlientRaw.h"
#include "Logger\Log.h"
#include <Ws2tcpip.h>

namespace SpEx {
	KlientRaw::KlientRaw(const std::string& nazwaPliku, FILE* fp, const std::string& ip, u_short port)
		: Watek(true), fp_(fp), nazwaPliku_(nazwaPliku), gniazdo_(INVALID_SOCKET), port_(port)
	{
		if (fp_ == nullptr) {
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Brak pliku!");
			return;
		}
		struct addrinfo *result = NULL;
		int errorCode;
		if (errorCode = getaddrinfo(ip.c_str(), nullptr, nullptr, &result)) {
			ustawBlad(STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(), STyp::Identyfikator(errorCode)));
			return;
		}

		decltype(addr_) &sock = *((decltype(addr_)*)(result->ai_addr));
		addr_.sin_family = AF_INET;
		addr_.sin_port = htons(port);
		addr_.sin_addr.s_addr = sock.sin_addr.s_addr;
		gniazdo_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	}
	
	bool KlientRaw::RecvData(SOCKET sock, void *buf, int buflen) const {
		char *pbuf = (char *)buf;
		while (buflen > 0){
			int num = recv(sock, pbuf, buflen, 0);
			if (num == SOCKET_ERROR){
				if (WSAGetLastError() == WSAEWOULDBLOCK){
					continue;
				}
				return false;
			}
			else if (num == 0)
				return false;
			pbuf += num;
			buflen -= num;
		}
		return true;
	}

	bool KlientRaw::RecvFile(SOCKET sock) const {
		long filesize;
		if (!RecvData(sock, &filesize, sizeof(filesize)))
			return false;
		filesize = ntohl(filesize);
		if (filesize > 0) {
			char buffer[1024];
			do {
				int num = min(filesize, sizeof(buffer));
				if (!RecvData(sock, buffer, num))
					return false;
				int offset = 0;
				do{
					size_t written = fwrite(&buffer[offset], 1, num - offset, fp_);
					if (written < 1)
						return false;
					offset += written;
				} while (offset < num);
				filesize -= num;
			} while (filesize > 0);
		}
		return true;
	}

	void KlientRaw::wykonuj() {
		if (fp_ == nullptr) {
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Brak pliku!");
			return;
		}

		// £¹czenie siê z serwerem
		if (SOCKET_ERROR == connect(gniazdo_, (struct sockaddr*) &addr_, sizeof(addr_))) {
			auto error = WSAGetLastError();
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Klient::pracujJakoKlient() -> B³¹d funkcji connect: " + std::to_string(error));
			zakoncz();
			ustawKodPowrotu(error);
			return;
		}

		RecvFile(gniazdo_);

	}

	KlientRaw::~KlientRaw()
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
