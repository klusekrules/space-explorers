#pragma once
#include <thread>
#include <atomic>

class Watek
{
public:
	Watek(void);
	virtual ~Watek(void);
	bool czekajNaZakonczenie();
	void zakoncz();
	bool zakonczony();
private:
	virtual void wykonuj();
	bool czyZakonczyc();
	std::thread* uchwyt_;
	std::atomic<bool> zakoncz_;
	std::atomic<bool> zakonczony_;
	void funkcjaWatku();
};

