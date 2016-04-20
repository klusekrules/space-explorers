#include "SocketBase.h"
#include <Ws2tcpip.h>
#include <thread>

#define ATRYBUT_PORT_SERWERA "portSerwera"
#define ATRYBUT_LIMIT_POLACZEN "limitPolaczen"
#define IP_BUFOR_K_ROZMIAR 20

SpEx::SocketBase::SocketBase(const UstawieniaAplikacji & opcje) {
	auto& port = opcje[ATRYBUT_PORT_SERWERA];
	if (!port.empty()) {
		port_ = std::stoi(port, nullptr, 10);
	}
	
	auto& maksymalnaIloscPolaczen = opcje[ATRYBUT_LIMIT_POLACZEN];
	if (!maksymalnaIloscPolaczen.empty()) {
		limitPolaczen_ = std::stoi(maksymalnaIloscPolaczen, nullptr, 10);
	}
}

SpEx::SocketBase::SocketBase(SOCKET gniazdo, struct sockaddr_in& info)
	: port_(0), gniazdo_(gniazdo), addr_(info)
{
	portUpdate();
}

int SpEx::SocketBase::pobierzPort(){
	if (port_ == 0 && gniazdo_ != INVALID_SOCKET)
		portUpdate();
	return port_;
}

void SpEx::SocketBase::ustawPort(int port){
	port_ = port;
}

const std::string & SpEx::SocketBase::pobierzAdres(){
	if (ip_.empty()) {
		char ip[IP_BUFOR_K_ROZMIAR];
		ZeroMemory(ip, IP_BUFOR_K_ROZMIAR);
		InetNtop(AF_INET, (void*)&addr_.sin_addr, ip, IP_BUFOR_K_ROZMIAR);
		ip_ = std::string(ip);
	}
	return ip_;
}

void SpEx::SocketBase::ustawAdres(const std::string & ip){
	ip_ = ip;
}

int SpEx::SocketBase::pobierzLimitPolaczen() const{
	return limitPolaczen_;
}

void SpEx::SocketBase::ustawLimitPolaczen(int limitPolaczen){
	limitPolaczen_ = limitPolaczen;
}

int SpEx::SocketBase::switchToNonBlockingMode(){
	u_long iMode = 1; //NonblockingMode
	if(SOCKET_ERROR == ioctlsocket(gniazdo_, FIONBIO, &iMode))
		return WSAGetLastError();
	return ERROR_SUCCESS;
}

int SpEx::SocketBase::switchToBlockingMode(){
	u_long iMode = 0; //BlockingMode
	if (SOCKET_ERROR == ioctlsocket(gniazdo_, FIONBIO, &iMode))
		return WSAGetLastError();
	return ERROR_SUCCESS;
}

SpEx::SocketBase::~SocketBase() {
	shutdown();
}

int SpEx::SocketBase::receive(char* bufor, int rozmiar, int flagi) const {
	return recv(gniazdo_, bufor, rozmiar, flagi);
}

int SpEx::SocketBase::send(const char* wiadomosc, int dlugosc, int flagi) const {
	return ::send(gniazdo_, wiadomosc, dlugosc, flagi);
}

std::string SpEx::SocketBase::translateIP(sockaddr_in & in){
	char ip[IP_BUFOR_K_ROZMIAR];
	ZeroMemory(ip, IP_BUFOR_K_ROZMIAR);
	InetNtop(AF_INET, (void*)&in.sin_addr, ip, IP_BUFOR_K_ROZMIAR);
	return std::string(ip);
}

int SpEx::SocketBase::socket(){
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port_);
	if(ip_.empty())
		addr.sin_addr.s_addr = INADDR_ANY;
	else
	{
		struct addrinfo *result = NULL;
		int errorCode = getaddrinfo(ip_.c_str(), nullptr, nullptr, &result);
		if (errorCode)
			return errorCode;
		decltype(addr_) &sock = *((decltype(addr_)*)(result->ai_addr));
		addr_.sin_addr.s_addr = sock.sin_addr.s_addr;
	}
	gniazdo_ = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (gniazdo_ == INVALID_SOCKET) {
		return WSAGetLastError();
	}
	addr_ = addr;
	return ERROR_SUCCESS;
}

int SpEx::SocketBase::bind(){
	if (SOCKET_ERROR == ::bind(gniazdo_, (struct sockaddr*) &addr_, sizeof(addr_))) {
		return WSAGetLastError();
	}
	return ERROR_SUCCESS;
}

int SpEx::SocketBase::listen(){
	if (SOCKET_ERROR == ::listen(gniazdo_, limitPolaczen_)) {
		return WSAGetLastError();
	}
	return ERROR_SUCCESS;
}

int SpEx::SocketBase::portUpdate(){
	struct sockaddr_in sin;
	socklen_t len = sizeof(sin);
	if (SOCKET_ERROR == getsockname(gniazdo_, (struct sockaddr *)&sin, &len))
		return WSAGetLastError();
	else
		port_ = ntohs(sin.sin_port);
	return ERROR_SUCCESS;
}

int SpEx::SocketBase::accept(SOCKET & gniazdo, struct sockaddr_in& addr){
	int addrlen = sizeof(struct sockaddr_in);
	gniazdo = ::accept(gniazdo_, (struct sockaddr*) &addr, &addrlen);
	return WSAGetLastError();
}

int SpEx::SocketBase::connect(){
	if (SOCKET_ERROR == ::connect(gniazdo_, (struct sockaddr*) &addr_, sizeof(addr_))) {
		return WSAGetLastError();
	}
	return ERROR_SUCCESS;
}

void SpEx::SocketBase::shutdown(){
	if (gniazdo_ != INVALID_SOCKET) {
		::shutdown(gniazdo_, SD_SEND);
		closesocket(gniazdo_);
		gniazdo_ = INVALID_SOCKET;
	}
}
