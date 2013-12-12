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
	char numerWatku_;
public:
	
	MenadzerWatkow( char iloscWatkow );
	void dodajZadanie( Zadanie& );
	virtual ~MenadzerWatkow();
};

