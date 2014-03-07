#pragma once
#include "Singleton.h"
#include "WatekZarzadzany.h"

class MenadzerWatkow 
	: se::NonCopyable, se::NonMoveable
{
private:

	class ElementListy 
		: se::NonCopyable
	{
	public:
		ElementListy();
		~ElementListy();
		ElementListy( ElementListy&& );
		void dodajZadanie( Zadanie& );

	private:
		std::shared_ptr<WatekZarzadzany> watek_;
		std::promise<bool> sygnal_;
	};

	std::mutex mutaxPuliWatkow_;
	std::vector<ElementListy> pulaWatkow_;
	char numerWatku_ = 0;
public:
	
	MenadzerWatkow() = default;
	void ustawLiczbeWatkow(unsigned char ilosc);
	void dodajZadanie( Zadanie& );
	virtual ~MenadzerWatkow() = default;
};

