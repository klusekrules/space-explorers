#pragma once
#include <string>
#include <algorithm>
#include "Zmiana\ZmianaInterfejs.h"
#include "PodstawoweParametry.h"

namespace SpEx{
	
	class STACKTHROW {
	public:
		static XmlBO::ElementWezla bladWezla(XmlBO::ElementWezla element, const std::string& nazwaWezla);

		static bool bladAtrybutu(XmlBO::ElementWezla element, const std::string& nazwaAtrybutu);

	};

	class Utils
	{
	public:

		static const STyp::Fluktuacja FMAX;
		static const STyp::Fluktuacja FMIN;

		static std::shared_ptr<SZmi::ZmianaInterfejs> TworzZmiane(XmlBO::ElementWezla);

		static std::shared_ptr<SZmi::ZmianaInterfejs> Kopiuj(std::shared_ptr<SZmi::ZmianaInterfejs> zmiana ){
			if (zmiana)
				return std::shared_ptr<SZmi::ZmianaInterfejs>(zmiana->Kopia());
			else
				return nullptr;
		}

		template<typename T>
		static T ObliczZmiane(std::shared_ptr<SZmi::ZmianaInterfejs> zmiana, const T& obiekt, const PodstawoweParametry& param){
			if (zmiana)
				return T(static_cast<T::nazwa_typu>(zmiana->policzWartosc(obiekt(), param.pobierzPoziom(), param.pobierzIdentyfikatorPlanety())()));
			else
				return obiekt;
		}

		static void generujWyjatekBleduStruktury(XmlBO::ElementWezla wezel);

		template<class Map, class Key>
		static bool zamianaKlucza(Map &kontener, Key &before, Key &after){
			if (kontener.find(after) != kontener.end())
				return false;
			auto iterator = kontener.find(before);
			if (iterator == kontener.end())
				return false;
			auto obiekt = iterator->second;
			kontener.erase(iterator);
			kontener.insert(make_pair(after, obiekt));
			return true;
		}

		static inline std::string trim(const std::string &s){
			auto  wsfront = std::find_if_not(s.begin(), s.end(), [](int c){return ::isspace(c); });
			return std::string(wsfront, std::find_if_not(s.rbegin(), std::string::const_reverse_iterator(wsfront), [](int c){return ::isspace(c); }).base());
		}

		static void ascii2hex(std::string& str, unsigned char c);
		static void sha3(std::string& str);

	};
}
