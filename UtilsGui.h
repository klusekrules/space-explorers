#pragma once
#include "MaszynaStanow.h"
#include <TGUI\TGUI.hpp>
#include "LogListGui.h"

namespace SpEx{
	class UtilsGui
	{
	public:
		template<class T>
		static typename T::Ptr PobierzWidzetZAktywnegoEkranu(const char * kontrolkaNazwy){
			return SpEx::MaszynaStanow::pobierzInstancje().pobierzOknoGry().pobierzStosEkranow().back()->pobierzGUI().get<T>(kontrolkaNazwy);
		}
		template<class T>
		static typename T::Ptr PobierzWidzetZWybranegoEkranu(int id, const char * kontrolkaNazwy){
			auto ekran = SpEx::MaszynaStanow::pobierzInstancje().pobierzOknoGry().pobierzEkran(id);
			if (ekran)
				return ekran->pobierzGUI().get<T>(kontrolkaNazwy);
			else
				return nullptr;
		}

		static void logToGUI(unsigned int, const std::string&);
		static void ustawOknoKomunikatow(int, const char *);
		static void odlaczOknoKomunikatow();
	private:
	};
};
