#pragma once
#include <string>
#include <vector>
#include <functional>

class PaczkaTestow
{
	friend class TestyJednostkowe;
public:
	PaczkaTestow() = default;
	virtual ~PaczkaTestow() = default;
	void ustawNazwe(const std::string& napis);
	void dodajTest(const std::string& nazwa, std::function<void()> test);
	virtual void startTestow();
	virtual void koniecTestow();
private:
	unsigned int bledy = 0;
	unsigned int bledyKrytyczne = 0;
	unsigned int pominieteTesty = 0;
	unsigned int poprawneTesty = 0;
	void wykonajTesty();
	void naglowek();
	void podsumowanie();
	std::string nazwa_;
	std::vector< std::pair< std::string, std::function<void()> > > zbiorTestow_;
};
