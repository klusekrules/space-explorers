#pragma once
#include <string>
#include <vector>
#include <functional>

using namespace std;

class PaczkaTestow
{
	friend class TestyJednostkowe;
public:
	PaczkaTestow();
	virtual ~PaczkaTestow();
	void ustawNazwe( const string& napis );
	void dodajTest( const string& nazwa, function<void ()> test );
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
	string nazwa_;
	vector< pair< string, function<void ()> > > zbiorTestow_;
};
