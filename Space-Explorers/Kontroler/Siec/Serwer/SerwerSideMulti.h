#pragma once
#include "KlientSideMulti.h"

namespace SpEx {
	class SerwerSideMulti 
		: public KlientSideMulti
	{
	public:
		// Konstruktor po stronie serwera.
		SerwerSideMulti(SOCKET gniazdo, struct sockaddr_in &addr);

	private:

		void pracujJakoSerwer();

	};
}