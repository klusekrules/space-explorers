#pragma once
#include <thread>
#include <atomic>
#include <mutex>

class Watek
{
public:
	Watek( bool wstrzymany );
	virtual ~Watek(void);
	bool czekajNaZakonczenie();
	void odblokuj();
	void zakoncz();
	std::atomic<bool>& zakonczony();

protected:	
	std::atomic<bool> zakoncz_;
	std::mutex wstrzymany_;
	std::atomic<bool> zakonczony_;

	virtual void wykonuj();
	std::atomic<bool>& czyZakonczyc();
	std::thread* uchwyt_;
	void funkcjaWatku();
};

