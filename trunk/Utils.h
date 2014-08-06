#pragma once
#include <string>
#include <algorithm>
#include "Zmiana\ZmianaInterfejs.h"
#include "PodstawoweParametry.h"

namespace SpEx{
	
	/**
	* \brief Klasa traitowa.
	*
	* Klasa definiuje specjalne zachowanie w przypadku wyst�pienia b��du w metodach pomocniczych parsera.
	* \author Daniel Wojdak
	* \version 1
	* \date 08-07-2014
	*/
	class STACKTHROW {
	public:
		/**
		* \brief Metoda generuj�ca wyj�tek.
		*
		* Metoda generuj�ca wyj�tek z opisem b��du w�z�a.
		* \param[in] element - B��dny w�ze�.
		* \param[in] nazwaWezla - Nazwa szukanego w�z�a.
		* \return Nie u�ywane.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		static XmlBO::ElementWezla bladWezla(XmlBO::ElementWezla element, const std::string& nazwaWezla);
		
		/**
		* \brief Metoda generuj�ca wyj�tek.
		*
		* Metoda generuj�ca wyj�tek z opisem b��du atrybutu.
		* \param[in] element - B��dny w�ze�.
		* \param[in] nazwaAtrybutu - Nazwa szukanego atrybutu.
		* \return Nie u�ywane.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		static bool bladAtrybutu(XmlBO::ElementWezla element, const std::string& nazwaAtrybutu);

	};


	/**
	* \brief Klasa z przydatnymi metodami.
	*
	* Klasa zawiera kilka przydatnych metod wykorzystywanych w aplikacji.
	* \author Daniel Wojdak
	* \version 2
	* \date 06-08-2014
	*/
	class Utils
	{
	public:

		static const STyp::Fluktuacja FMAX; /// Sta�a okre�laj�ca maksymaln� dopuszczaln� warto�� fluktuacji.
		static const STyp::Fluktuacja FMIN; /// Sta�a okre�laj�ca minimaln� dopuszczaln� warto�� fluktuacji.

		/**
		* \brief Metoda konwertuj�ca czas na napis.
		*
		* Metoda konwertuje czas przekazany w atrybucie na napis.
		* \param[in] czas - Czas do konwersji.
		* \return Napis zawieraj�cy skonwertowany czas.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		* \todo Metoda u�ywana tylko w klasie GUI. Przenie�� do UtilsGui.
		*/
		static std::string konwersja( const STyp::Czas& czas );

		/**
		* \brief Metoda tworz�ca zamian�.
		*
		* Metoda tworzy zmian� na podstawie w�z�a przekazanego przez atrybut.
		* \param[in] wezel - W�ze� opisuj�cy zmian�.
		* \return Wska�nik do zmiany, je�eli tworzenie powiedzie si� lub nullptr, je�eli wyst�pi b��d.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		* \todo Metoda powinna by� przeniesiona do zarz�dcy pami�ci.
		*/
		static std::shared_ptr<SZmi::ZmianaInterfejs> TworzZmiane(XmlBO::ElementWezla wezel);

		/**
		* \brief Metoda kopiuj�ca zamian�.
		*
		* Metoda tworzy kopi� zmiany przekazanej przez atrybut.
		* \param[in] zmiana - Zmiana do skopiowania.
		* \return Wska�nik do zmiany, je�eli kopiowanie powiedzie si� lub nullptr, je�eli wyst�pi b��d.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		* \todo Metoda powinna by� przeniesiona do zarz�dcy pami�ci.
		*/
		static std::shared_ptr<SZmi::ZmianaInterfejs> Kopiuj(std::shared_ptr<SZmi::ZmianaInterfejs> zmiana ){
			if (zmiana)
				return std::shared_ptr<SZmi::ZmianaInterfejs>(zmiana->Kopia());
			else
				return nullptr;
		}

		/**
		* \brief Metoda obliczaj�ca warto�� zmiany.
		*
		* Metoda wylicza warto�� zmiany dla podanych parametr�w.
		* \param[in] zmiana - Zmiana dla kt�rej wyliczana jest warto��.
		* \param[in] obiekt - Obiekt dla kt�rego wyliczana jest warto��.
		* \param[in] param - Podstawowe parametry dla kt�rych wyliczana jest warto��.
		* \return Wyliczona warto�� zmiany, je�eli powiedzie si� oblicznie zmiany. Warto�� obiektu, je�eli zmiana jest niepoprawna.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		template<typename T>
		static T ObliczZmiane(std::shared_ptr<SZmi::ZmianaInterfejs> zmiana, const T& obiekt, const PodstawoweParametry& param){
			if (zmiana)
				return T(static_cast<T::nazwa_typu>(zmiana->policzWartosc(obiekt(), param.pobierzPoziom(), param.pobierzIdentyfikatorPlanety())()));
			else
				return obiekt;
		}

		/**
		* \brief Metoda generuj�ca wyj�tek.
		*
		* Metoda generuje wyj�tek opisuj�cy w�ze� podany w atrybucie.
		* \param[in] wezel - W�ze�, w kt�rym wyst�pi� b��d.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		static void generujWyjatekBleduStruktury(XmlBO::ElementWezla wezel);

		/**
		* \brief Metoda zamieniaj�ca klucz dla warto�ci w mapie.
		*
		* Metoda zamienia klucz dla warto�ci.
		* \param[inout] kontener - Mapa, w kt�rej zamieniany jest klucz.
		* \param[in] before - Stara warto�� klucza.
		* \param[in] after - Nowa warto�� klucza.
		* \return Zwracana jest warto�� true, je�eli metoda zako�czy si� powowdzeniem. Zwracana jest warto�� false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
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

		/**
		* \brief Metoda trymuj�ca ci�g znak�w.
		*
		* Metoda usuwa z ci�gu znak�w pocz�tkowe i ko�cowe bia�e znaki.
		* \param[in] s - Ci�g znak�w.
		* \return Zwracany jest ci�g znak�w bez ko�cowych i pocz�kowych bia�ych znak�w.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		static inline std::string trim(const std::string &s){
			auto  wsfront = std::find_if_not(s.begin(), s.end(), [](int c){return ::isspace(c); });
			return std::string(wsfront, std::find_if_not(s.rbegin(), std::string::const_reverse_iterator(wsfront), [](int c){return ::isspace(c); }).base());
		}

		/**
		* \brief Metoda zapisuj�ca bajt w postaci szesnastkowej.
		*
		* Metoda dodaje do napisu bajt zapisany w postaci szesnastkowej.
		* \param[out] str - Ci�g znak�w.
		* \param[in] c - Bajt do konwersji.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		static void ascii2hex(std::string& str, unsigned char c);

		/**
		* \brief Metoda oblicza sum� sha3 podanego ci�gu.
		*
		* Metoda zamienia podany ci�g na jego sum� sha3. U�ywany jest do tego algorytm keccak
		* \param[inout] str - Ci�g znak�w.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		static void sha3(std::string& str);

		/**
		* \brief Metoda wyodr�bnia rozsze�enie pliku.
		*
		* Metoda wyodr�bnia rozsze�enie pliku zawartego w adresie.
		* \param[in] adres - Adres pliku.
		* \param[out] rozszezenie - Rozsze�enie pliku znajduj�cego.
		* \return Zwracana jest warto�� true je�eli uda si� wyodr�bni� rozsze�enie, zwracana jest warto�� false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		static bool pobierzRozszezenie(const std::string & adres, std::string& rozszezenie);

	};
}
