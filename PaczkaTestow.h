#pragma once
#include <string>
#include <vector>
#include <functional>

class PaczkaTestow
{
	friend class TestyJednostkowe;
public:
	PaczkaTestow();
	virtual ~PaczkaTestow();
	void ustawNazwe(const std::string& napis);
	void dodajTest(const std::string& nazwa, std::function<void()> test);
	virtual void startTestow();
	virtual void koniecTestow();
private:
	unsigned int bledy;
	unsigned int bledyKrytyczne;
	unsigned int pominieteTesty;
	unsigned int poprawneTesty;
	void wykonajTesty();
	void naglowek();
	void podsumowanie();
	std::string nazwa_;
	std::vector< std::pair< std::string, std::function<void()> > > zbiorTestow_;
};
