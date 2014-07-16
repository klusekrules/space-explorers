#pragma once
#include "NieznalezionoObiektu.h"
#include "Obiekt.h"
#include "ListaObiektow.hpp"
#include "PodstawoweParametry.h"
#include "Surowce.h"

namespace SpEx{

	class LadowniaInfo;
	class Statek;
	/**
	* \brief Klasa preprezentuj¹ca ³adownie statku.
	*
	* Klasa s³u¿y do przechowywania i zarz¹dzania obiektami w ³adowni.
	* \author Daniel Wojdak
	* \version 2
	* \date 16-07-2014
	*/
	class Ladownia :
		virtual public PodstawoweParametry,
		virtual public SLog::LoggerInterface,
		virtual public Serializacja
	{
	public:
		typedef Surowce Item;
		typedef ListaObiektow< Item > Zbiornik;
		typedef std::vector < STyp::Identyfikator > ListaKluczy;

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] ilosc - Iloœæ tworzonych obiektów.
		* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
		* \param[in] ladowniaInfo - Referencja do obiektu opisuj¹cego.
		* \author Daniel Wojdak
		* \version 2
		* \date 16-07-2014
		*/
		Ladownia(const STyp::Ilosc& ilosc, const STyp::Identyfikator& identyfikatorPlanety, const LadowniaInfo& ladowniaInfo);

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] podstawoweParametry - Podstawowe parametry tworzonych obiektów.
		* \param[in] ladowniaInfo - Referencja do obiektu opisuj¹cego.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		Ladownia(const PodstawoweParametry& podstawoweParametry, const LadowniaInfo& ladowniaInfo);

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~Ladownia() = default;

		/**
		* \brief Metoda wyliczaj¹ca procent wolnego miejsca.
		*
		* Metoda obliczaj¹ca wolne miejsce w ³adowni.
		* \return Procentowa wartoœæ wolnego miejsca w ³adowni.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		STyp::Fluktuacja wolneMiejsceLadowni() const;

		/**
		* \brief Metoda dodaj¹ca obiekt do ³adowni.
		*
		* Metoda dodaj¹ca obiekt do ³adowni.
		* \param[in] obiekt - Obiekt dodawany do ³adowni.
		* \return true je¿eli dodano obiekt, false w przeciwnym wypadku.
		* \remark Metoda tworzy kopie elementu. Metoda tranzakcyjna.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		bool dodajObiektDoLadowni(const Item& obiekt);

		/**
		* \brief Metoda dodaj¹ca obiekt do ³adowni.
		*
		* Metoda dodaj¹ca obiekt do ³adowni.
		* \param[in] obiekt - Obiekt dodawany do ³adowni.
		* \return true je¿eli dodano obiekt, false w przeciwnym wypadku.
		* \remark Metoda nie tworzy kopii elementu. Metoda tranzakcyjna.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		bool dodajObiektDoLadowni(std::shared_ptr<Item> obiekt);

		/**
		* \brief Metoda wylicza objêtoœæ maksymaln¹ ³adowni.
		*
		* Metoda wyliczaj¹ca maksymaln¹ objêtoœæ ³adowni.
		* \return Objêtoœæ maksymalna ³adowni.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		virtual STyp::Objetosc pobierzPojemnoscMaksymalnaLadowni() const;

		/**
		* \brief Metoda pobieraj¹ca pojemnoœæ jednostkow¹
		*
		* Metoda obliczaj¹ca pojemnoœæ jednostkow¹ ³adowni.
		* \return Objêtoœæ jednostkowa ³adowni.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		STyp::Objetosc pobierzPojemnoscJednostkowaLadowni() const;

		/**
		* \brief Metoda ³¹czy obiekty ³adowni.
		*
		* Metoda przenosi obiekty z ³adowni przekazanej przez parametr do obiektu docelowego.
		* \param[in] ladownia - £adownia Ÿród³owa.
		* \return true je¿eli uda siê przenieœæ, false w przeciwnym wypadku.
		* \remark Metoda tranzakcyjna.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		bool polaczLadownie(Ladownia& ladownia);

		/**
		* \brief Metoda ³¹czy obiekty ³adowni.
		*
		* Metoda przenosi obiekty z ³adowni przekazanej przez parametr do obiektu docelowego.
		* \param[in] zbiornik - £adownia Ÿród³owa.
		* \return true je¿eli uda siê przenieœæ, false w przeciwnym wypadku.
		* \remark Metoda tranzakcyjna.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		bool polaczLadownie(Zbiornik zbiornik);

		/**
		* \brief Metoda pobiera iloœæ obiektów o podanym kluczu.
		*
		* Metoda pobieraj¹ca iloœæ obiektów, o kluczu przekazanym w parametrze, znajduj¹cych siê w ³adowni.
		* \param[in] klucz - Klucz identyfikuj¹cy obiekt.
		* \return Iloœæ obiektów o podanym kluczu znajduj¹ca siê w ³adowni.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		STyp::Ilosc pobierzIloscObiektowLadowni(const STyp::Identyfikator& klucz) const;

		/**
		* \brief Metoda wyjmuje z ³adowni obietk o podanym kluczu i podanej iloœci
		*
		* Metoda wyjmuj¹ca obiekt z ³adowni.
		* \param[in] klucz - Klucz identyfikuj¹cy obiekt.
		* \param[in] ilosc - Iloœæ obiektów o podanym kluczu.
		* \return WskaŸnik na wyjêty obiekt. nullptr je¿eli wystapi³ b³ad.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		std::shared_ptr<Item> wyjmijObiektZLadowni(const STyp::Identyfikator& klucz, const STyp::Ilosc& ilosc);

		/**
		* \brief Metoda zwraca listê kluczy obiektów.
		*
		* Metoda generuje listê kluczy wszystkich obiektów znajduj¹cych sie w ³adowni.
		* \return Lista kluczy obiektów znajduj¹cych sie w ³adowni.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		ListaKluczy pobierzListeIdentyfikatorowObiektowLadowni() const;

		/**
		* \brief Metoda zwraca listê obiektów znajduj¹cych siê w ³adowni.
		*
		* Metoda zwraca obiekty jakie znajduj¹ sie w ³adowni.
		* \return Lista obiektów znajduj¹cych siê w ³adowni.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		const Zbiornik& pobierzPrzewozoneObiektyLadowni() const;

		/**
		* \brief Metoda dzieli ³adownie.
		*
		* Metoda dzieli ³adownie w taki sposób, aby objêtoœæ odzielonej czêœci ³adowni zawiera³ siê w przedziale \<minimum,maksimum\>.
		* \param[in] minimum - Minimalna objêtoœæ wydzielanej czeœci.
		* \param[in] maksimum - Maksymalna objêtoœæ wydzielanej czeœci.
		* \return Zbiornik z elementami.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		Zbiornik podzielLadownie(const STyp::Objetosc& minimum, const STyp::Objetosc& maksimum);

		/**
		* \brief Metoda zwraca objêtoœæ wszystkich elementów w zbiorniku.
		*
		* Metoda oblicza zajêtê miejsce w ³adowni.
		* \return Objêtoœæ elementów w ³adowni.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		const STyp::Objetosc& pobierzZajeteMiejsceLadowni() const;

		/**
		* \brief Metoda zwraca dostêpn¹ przestrzeñ ³adowni.
		*
		* Metoda obliczaj¹ca dostêpne miejsce w ³adowni.
		* \return Dostêpna przestrzeñ ³adowni.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		STyp::Objetosc pobierzDostepneMiejsceLadowni() const;

		/**
		* \brief Metoda opró¿nia ³adownie.
		*
		* Metoda zwraca wszystkie obiekty znajduj¹ce siê w ³adowni. Pozostawia ³adownie pust¹.
		* \return Zbiornik zawieraj¹cy obiekty.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		Zbiornik oproznijLadownie();

		/**
		* \brief Metoda zapisuj¹ca.
		*
		* Metoda s³u¿¹ca do zapisu danych do wêz³a xml podanego jako parametr.
		* \param[out] wezel - Wêze³ do którego s¹ zapisywane dane.
		* \return Zwracana jest wartoœæ true, je¿eli zapisano obiekt poprawnie. False, je¿eli zapis siê nie powiód³.
		* \warning Je¿eli zwrócono wartoœæ false wêze³ przekazany jako parametr nie jest zmodyfokowany.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		bool zapisz(XmlBO::ElementWezla wezel) const override;

		/**
		* \brief Metoda odczytuj¹ca.
		*
		* Metoda s³u¿¹ca do odczytu danych z wêz³a xml podanego jako parametr.
		* \param[in] wezel - Wêze³ z którego s¹ odczytywane dane.
		* \return Zwracana jest wartoœæ true, je¿eli odczytano obiekt poprawnie. False, je¿eli odczyt siê nie powiód³.
		* \warning Metoda nie modyfikuje wêz³a.
		* \warning Je¿eli metoda zwróci wartoœæ false, obiekt mo¿e znajdowaæ siê w stanie nieustalonym. Nie jest zalecane u¿ywanie takiego obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		*/
		std::string napis()const override;

	protected:

		/**
		* \brief Metoda przeliczaj¹ca zajête miejsce w ³adowni.
		*
		* Metoda przeliczaj¹ca zajête miejsce w ³adowni.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		void przeliczZajeteMiejsceLadowni();

		/**
		* \brief Metoda pobieraj¹ca masê obiektów znajduj¹cych siê w ³adowni.
		*
		* Metoda wyliczaj¹ca masê obiektów w ³adowni.
		* \return Masa obiektów w ³adowni.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		STyp::Masa pobierzMaseZawartosciLadowni()const;

		Zbiornik obiekty_; /// Lista elementów w ³adowni.
		STyp::Objetosc zajete_; /// Zajête miejsce.

	private:
		const LadowniaInfo& ladowniaInfo_; /// Referencja do obiektu opisuj¹cego.
	};
}
