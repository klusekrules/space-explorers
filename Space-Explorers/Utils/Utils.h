#pragma once
#include <string>
#include <algorithm>
#include <vector>
#include "Parser\ParserInterfejs.h"
#include "Zmiana\ZmianaInterfejs.h"
#include "Model\PodstawoweParametry.h"
#include "Logger\Log.h"

namespace SpEx{
	
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


		static std::string pobierzDebugInfo();

		static __int64 pobierzLiczbeLosowa();

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
			auto  wsfront = std::find_if_not(s.begin(), s.end(), [](unsigned char c){return ::isspace(c); });
			return std::string(wsfront, std::find_if_not(s.rbegin(), std::string::const_reverse_iterator(wsfront), [](unsigned char c){return ::isspace(c); }).base());
		}

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

		static std::vector < SLog::Log::TypLogow > dekodujListeTypowLogow(const std::string& str);

		static bool tworzSciezke(const std::string& path);

		static void generujSzablonPlikuGry(std::shared_ptr<SPar::ParserDokument>& ptr);

	};
}
