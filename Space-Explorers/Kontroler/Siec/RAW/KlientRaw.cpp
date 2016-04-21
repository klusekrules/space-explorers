#include "KlientRaw.h"
#include "Logger\Log.h"
#include <Ws2tcpip.h>

namespace SpEx {
	KlientRaw::KlientRaw(const std::string& nazwaPliku, FILE* fp, const std::string& ip, u_short port)
		: Watek(true), fp_(fp), nazwaPliku_(nazwaPliku)
	{
		if (fp_ == nullptr) {
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Brak pliku!");
			return;
		}
		ustawAdres(ip);
		ustawPort(port);
		socket();
	}
	
	bool KlientRaw::RecvData(void *buf, int buflen) {
		char *pbuf = (char *)buf;
		while (buflen > 0){
			int num = receive(pbuf, buflen);
			if (num == SOCKET_ERROR){
				error_ = WSAGetLastError();
				if (error_ == WSAEWOULDBLOCK){
					continue;
				}
				return false;
			}
			else if (num == 0) {
				error_ = 0;
				return false;
			}
			pbuf += num;
			buflen -= num;
		}
		return true;
	}

	bool KlientRaw::RecvFile() {
		long filesize;
		if (!RecvData(&filesize, sizeof(filesize)))
			return false;
		filesize = ntohl(filesize);
		if (filesize > 0) {
			char buffer[1024];
			do {
				int num = min(filesize, sizeof(buffer));
				if (!RecvData(buffer, num))
					return false;
				int offset = 0;
				do{
					size_t written = fwrite(&buffer[offset], sizeof(char), num - offset, fp_);
					if (written == 0) {
						error_ = ferror(fp_);
						return false;
					}
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

		int error = connect();
		if (error != ERROR_SUCCESS) {
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "KlientRaw::wykonuj() -> B³¹d funkcji connect: " + std::to_string(error));
			zakoncz();
			ustawKodPowrotu(error);
			return;
		}
		
		if (!RecvFile()) {
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "KlientRaw::wykonuj() -> B³¹d funkcji RecvFile: " + std::to_string(error));
			zakoncz();
			ustawKodPowrotu(error);
			return;
		}

		SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Pobrano plik: " + nazwaPliku_);
	}

	KlientRaw::~KlientRaw(){
		if (fp_ != nullptr) {
			fclose(fp_);
		}
	}
}
