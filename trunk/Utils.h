#pragma once
#include <string>
#include <algorithm>
#include "Zmiana\ZmianaInterfejs.h"
#include "PodstawoweParametry.h"

namespace SpEx{
	
	/**
	* \brief Klasa traitowa.
	*
	* Klasa definiuje specjalne zachowanie w przypadku wyst¹pienia b³êdu w metodach pomocniczych parsera.
	* \author Daniel Wojdak
	* \version 1
	* \date 08-07-2014
	*/
	class STACKTHROW {
	public:
		/**
		* \brief Metoda generuj¹ca wyj¹tek.
		*
		* Metoda generuj¹ca wyj¹tek z opisem b³êdu wêz³a.
		* \param[in] element - B³êdny wêze³.
		* \param[in] nazwaWezla - Nazwa szukanego wêz³a.
		* \return Nie u¿ywane.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		static XmlBO::ElementWezla bladWezla(XmlBO::ElementWezla element, const std::string& nazwaWezla);
		
		/**
		* \brief Metoda generuj¹ca wyj¹tek.
		*
		* Metoda generuj¹ca wyj¹tek z opisem b³êdu atrybutu.
		* \param[in] element - B³êdny wêze³.
		* \param[in] nazwaAtrybutu - Nazwa szukanego atrybutu.
		* \return Nie u¿ywane.
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

		static const STyp::Fluktuacja FMAX; /// Sta³a okreœlaj¹ca maksymaln¹ dopuszczaln¹ wartoœæ fluktuacji.
		static const STyp::Fluktuacja FMIN; /// Sta³a okreœlaj¹ca minimaln¹ dopuszczaln¹ wartoœæ fluktuacji.

		/**
		* \brief Metoda konwertuj¹ca czas na napis.
		*
		* Metoda konwertuje czas przekazany w atrybucie na napis.
		* \param[in] czas - Czas do konwersji.
		* \return Napis zawieraj¹cy skonwertowany czas.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		* \todo Metoda u¿ywana tylko w klasie GUI. Przenieœæ do UtilsGui.
		*/
		static std::string konwersja( const STyp::Czas& czas );

		/**
		* \brief Metoda tworz¹ca zamianê.
		*
		* Metoda tworzy zmianê na podstawie wêz³a przekazanego przez atrybut.
		* \param[in] wezel - Wêze³ opisuj¹cy zmianê.
		* \return WskaŸnik do zmiany, je¿eli tworzenie powiedzie siê lub nullptr, je¿eli wyst¹pi b³¹d.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		* \todo Metoda powinna byæ przeniesiona do zarz¹dcy pamiêci.
		*/
		static std::shared_ptr<SZmi::ZmianaInterfejs> TworzZmiane(XmlBO::ElementWezla wezel);

		/**
		* \brief Metoda kopiuj¹ca zamianê.
		*
		* Metoda tworzy kopiê zmiany przekazanej przez atrybut.
		* \param[in] zmiana - Zmiana do skopiowania.
		* \return WskaŸnik do zmiany, je¿eli kopiowanie powiedzie siê lub nullptr, je¿eli wyst¹pi b³¹d.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		* \todo Metoda powinna byæ przeniesiona do zarz¹dcy pamiêci.
		*/
		static std::shared_ptr<SZmi::ZmianaInterfejs> Kopiuj(std::shared_ptr<SZmi::ZmianaInterfejs> zmiana ){
			if (zmiana)
				return std::shared_ptr<SZmi::ZmianaInterfejs>(zmiana->Kopia());
			else
				return nullptr;
		}

		/**
		* \brief Metoda obliczaj¹ca wartoœæ zmiany.
		*
		* Metoda wylicza wartoœæ zmiany dla podanych parametrów.
		* \param[in] zmiana - Zmiana dla której wyliczana jest wartoœæ.
		* \param[in] obiekt - Obiekt dla którego wyliczana jest wartoœæ.
		* \param[in] param - Podstawowe parametry dla których wyliczana jest wartoœæ.
		* \return Wyliczona wartoœæ zmiany, je¿eli powiedzie siê oblicznie zmiany. Wartoœæ obiektu, je¿eli zmiana jest niepoprawna.
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
		* \brief Metoda generuj¹ca wyj¹tek.
		*
		* Metoda generuje wyj¹tek opisuj¹cy wêze³ podany w atrybucie.
		* \param[in] wezel - Wêze³, w którym wyst¹pi³ b³¹d.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		static void generujWyjatekBleduStruktury(XmlBO::ElementWezla wezel);

		/**
		* \brief Metoda zamieniaj¹ca klucz dla wartoœci w mapie.
		*
		* Metoda zamienia klucz dla wartoœci.
		* \param[inout] kontener - Mapa, w której zamieniany jest klucz.
		* \param[in] before - Stara wartoœæ klucza.
		* \param[in] after - Nowa wartoœæ klucza.
		* \return Zwracana jest wartoœæ true, je¿eli metoda zakoñczy siê powowdzeniem. Zwracana jest wartoœæ false w przeciwnym wypadku.
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
		* \brief Metoda trymuj¹ca ci¹g znaków.
		*
		* Metoda usuwa z ci¹gu znaków pocz¹tkowe i koñcowe bia³e znaki.
		* \param[in] s - Ci¹g znaków.
		* \return Zwracany jest ci¹g znaków bez koñcowych i pocz¹kowych bia³ych znaków.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		static inline std::string trim(const std::string &s){
			auto  wsfront = std::find_if_not(s.begin(), s.end(), [](int c){return ::isspace(c); });
			return std::string(wsfront, std::find_if_not(s.rbegin(), std::string::const_reverse_iterator(wsfront), [](int c){return ::isspace(c); }).base());
		}

		/**
		* \brief Metoda zapisuj¹ca bajt w postaci szesnastkowej.
		*
		* Metoda dodaje do napisu bajt zapisany w postaci szesnastkowej.
		* \param[out] str - Ci¹g znaków.
		* \param[in] c - Bajt do konwersji.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		static void ascii2hex(std::string& str, unsigned char c);

		/**
		* \brief Metoda oblicza sumê sha3 podanego ci¹gu.
		*
		* Metoda zamienia podany ci¹g na jego sumê sha3. U¿ywany jest do tego algorytm keccak
		* \param[inout] str - Ci¹g znaków.
		* \author Daniel Wojdak
		* \version 1
		* \date 08-07-2014
		*/
		static void sha3(std::string& str);

		/**
		* \brief Metoda wyodrêbnia rozsze¿enie pliku.
		*
		* Metoda wyodrêbnia rozsze¿enie pliku zawartego w adresie.
		* \param[in] adres - Adres pliku.
		* \param[out] rozszezenie - Rozsze¿enie pliku znajduj¹cego.
		* \return Zwracana jest wartoœæ true je¿eli uda siê wyodrêbniæ rozsze¿enie, zwracana jest wartoœæ false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		static bool pobierzRozszezenie(const std::string & adres, std::string& rozszezenie);

	};
}
