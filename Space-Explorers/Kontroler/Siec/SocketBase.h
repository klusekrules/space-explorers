#pragma once
#include "Narzedzia\UstawieniaAplikacji.h"
#include <WinSock2.h>

namespace SpEx {
	class SocketBase
	{
		friend class GniazdoWinSock;
	public:
		SocketBase() = default;
		SocketBase(SOCKET, struct sockaddr_in&);
		SocketBase(const UstawieniaAplikacji& opcje);
		int pobierzPort();
		void ustawPort(int);
		const std::string & pobierzAdres();
		void ustawAdres( const std::string& );
		int pobierzLimitPolaczen() const;
		void ustawLimitPolaczen(int);
		int switchToNonBlockingMode();
		int switchToBlockingMode();
		virtual ~SocketBase();

		GniazdoWinSock pobierzGniazdo();
		static std::string translateIP(struct sockaddr_in&);

	protected:
		int socket();
		int bind();
		int listen();
		int portUpdate();
		int accept(SOCKET&, struct sockaddr_in& );
		int acceptWithTimeout(SOCKET&, struct sockaddr_in&, long seconds);
		int connect();
		void shutdown();
		int receive(char*, int, int = 0) const;
		int send(const char*, int, int = 0) const;

	private:
		int port_ = 0;
		int limitPolaczen_ = SOMAXCONN;
		std::string ip_;

		SOCKET gniazdo_ = INVALID_SOCKET;
		struct sockaddr_in addr_;
	};
}