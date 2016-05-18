#include "DaneTCP.h"
#include <WinSock2.h>
#include <vector>
#include "Logger\Log.h"
#include "RPC\StaleRPC.h"
#include <chrono>
#include <thread>

int SpEx::DaneTCP::wyslij(){
	int rezultat = 0;
	u_int64 header = 0;

	rezultat = dane_.przygotujDane();

	if (rezultat != ERROR_SUCCESS) {
		return rezultat;
	}

	header = htonll(dane_.pobierzFlagi());

	gniazdo_.ustawWarunekOczekiwania(warunek_);
	rezultat = gniazdo_.wyslij((char*)&header, sizeof(u_int64));
	gniazdo_.ustawWarunekOczekiwania(nullptr);

	if (warunek_())
		return SOCK_CONNECTION_CLOSED;

	if (rezultat != ERROR_SUCCESS)
		return rezultat;
	
	gniazdo_.ustawWarunekOczekiwania(warunek_);
	rezultat = gniazdo_.wyslij(dane_);
	gniazdo_.ustawWarunekOczekiwania(nullptr);

	if (warunek_())
		return SOCK_CONNECTION_CLOSED;

	if (rezultat != ERROR_SUCCESS)
		return rezultat;

	return ERROR_SUCCESS;
}

int SpEx::DaneTCP::odbierz(){
	u_int64 header = 0;
	int rezultat = 0;
	
	gniazdo_.ustawWarunekOczekiwania(warunek_);
	rezultat = gniazdo_.odbierz((char*)&header, sizeof(u_int64)); 
	gniazdo_.ustawWarunekOczekiwania(nullptr);

	if (warunek_())
		return SOCK_CONNECTION_CLOSED;

	if (rezultat != ERROR_SUCCESS)
		return rezultat;
	
	dane_.ustawFlagi(ntohll(header));

	gniazdo_.ustawWarunekOczekiwania(warunek_);
	rezultat = gniazdo_.odbierz(dane_);
	gniazdo_.ustawWarunekOczekiwania(nullptr);
	
	if (warunek_())
		return SOCK_CONNECTION_CLOSED;

	if (rezultat != ERROR_SUCCESS)
		return rezultat;
	
	if (dane_.rozmiar() > 0)
		return dane_.przygotujDane();
	else
		return ERROR_LACK_OF_DATA;
}
