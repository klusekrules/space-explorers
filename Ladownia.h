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
	* \brief Klasa preprezentuj�ca �adownie statku.
	*
	* Klasa s�u�y do przechowywania i zarz�dzania obiektami w �adowni.
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
		* \param[in] ilosc - Ilo�� tworzonych obiekt�w.
		* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
		* \param[in] ladowniaInfo - Referencja do obiektu opisuj�cego.
		* \author Daniel Wojdak
		* \version 2
		* \date 16-07-2014
		*/
		Ladownia(const STyp::Ilosc& ilosc, const STyp::Identyfikator& identyfikatorPlanety, const LadowniaInfo& ladowniaInfo);

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] podstawoweParametry - Podstawowe parametry tworzonych obiekt�w.
		* \param[in] ladowniaInfo - Referencja do obiektu opisuj�cego.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		Ladownia(const PodstawoweParametry& podstawoweParametry, const LadowniaInfo& ladowniaInfo);

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~Ladownia() = default;

		/**
		* \brief Metoda wyliczaj�ca procent wolnego miejsca.
		*
		* Metoda obliczaj�ca wolne miejsce w �adowni.
		* \return Procentowa warto�� wolnego miejsca w �adowni.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		STyp::Fluktuacja wolneMiejsceLadowni() const;

		/**
		* \brief Metoda dodaj�ca obiekt do �adowni.
		*
		* Metoda dodaj�ca obiekt do �adowni.
		* \param[in] obiekt - Obiekt dodawany do �adowni.
		* \return true je�eli dodano obiekt, false w przeciwnym wypadku.
		* \remark Metoda tworzy kopie elementu. Metoda tranzakcyjna.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		bool dodajObiektDoLadowni(const Item& obiekt);

		/**
		* \brief Metoda dodaj�ca obiekt do �adowni.
		*
		* Metoda dodaj�ca obiekt do �adowni.
		* \param[in] obiekt - Obiekt dodawany do �adowni.
		* \return true je�eli dodano obiekt, false w przeciwnym wypadku.
		* \remark Metoda nie tworzy kopii elementu. Metoda tranzakcyjna.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		bool dodajObiektDoLadowni(std::shared_ptr<Item> obiekt);

		/**
		* \brief Metoda wylicza obj�to�� maksymaln� �adowni.
		*
		* Metoda wyliczaj�ca maksymaln� obj�to�� �adowni.
		* \return Obj�to�� maksymalna �adowni.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		virtual STyp::Objetosc pobierzPojemnoscMaksymalnaLadowni() const;

		/**
		* \brief Metoda pobieraj�ca pojemno�� jednostkow�
		*
		* Metoda obliczaj�ca pojemno�� jednostkow� �adowni.
		* \return Obj�to�� jednostkowa �adowni.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		STyp::Objetosc pobierzPojemnoscJednostkowaLadowni() const;

		/**
		* \brief Metoda ��czy obiekty �adowni.
		*
		* Metoda przenosi obiekty z �adowni przekazanej przez parametr do obiektu docelowego.
		* \param[in] ladownia - �adownia �r�d�owa.
		* \return true je�eli uda si� przenie��, false w przeciwnym wypadku.
		* \remark Metoda tranzakcyjna.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		bool polaczLadownie(Ladownia& ladownia);

		/**
		* \brief Metoda ��czy obiekty �adowni.
		*
		* Metoda przenosi obiekty z �adowni przekazanej przez parametr do obiektu docelowego.
		* \param[in] zbiornik - �adownia �r�d�owa.
		* \return true je�eli uda si� przenie��, false w przeciwnym wypadku.
		* \remark Metoda tranzakcyjna.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		bool polaczLadownie(Zbiornik zbiornik);

		/**
		* \brief Metoda pobiera ilo�� obiekt�w o podanym kluczu.
		*
		* Metoda pobieraj�ca ilo�� obiekt�w, o kluczu przekazanym w parametrze, znajduj�cych si� w �adowni.
		* \param[in] klucz - Klucz identyfikuj�cy obiekt.
		* \return Ilo�� obiekt�w o podanym kluczu znajduj�ca si� w �adowni.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		STyp::Ilosc pobierzIloscObiektowLadowni(const STyp::Identyfikator& klucz) const;

		/**
		* \brief Metoda wyjmuje z �adowni obietk o podanym kluczu i podanej ilo�ci
		*
		* Metoda wyjmuj�ca obiekt z �adowni.
		* \param[in] klucz - Klucz identyfikuj�cy obiekt.
		* \param[in] ilosc - Ilo�� obiekt�w o podanym kluczu.
		* \return Wska�nik na wyj�ty obiekt. nullptr je�eli wystapi� b�ad.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		std::shared_ptr<Item> wyjmijObiektZLadowni(const STyp::Identyfikator& klucz, const STyp::Ilosc& ilosc);

		/**
		* \brief Metoda zwraca list� kluczy obiekt�w.
		*
		* Metoda generuje list� kluczy wszystkich obiekt�w znajduj�cych sie w �adowni.
		* \return Lista kluczy obiekt�w znajduj�cych sie w �adowni.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		ListaKluczy pobierzListeIdentyfikatorowObiektowLadowni() const;

		/**
		* \brief Metoda zwraca list� obiekt�w znajduj�cych si� w �adowni.
		*
		* Metoda zwraca obiekty jakie znajduj� sie w �adowni.
		* \return Lista obiekt�w znajduj�cych si� w �adowni.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		const Zbiornik& pobierzPrzewozoneObiektyLadowni() const;

		/**
		* \brief Metoda dzieli �adownie.
		*
		* Metoda dzieli �adownie w taki spos�b, aby obj�to�� odzielonej cz�ci �adowni zawiera� si� w przedziale \<minimum,maksimum\>.
		* \param[in] minimum - Minimalna obj�to�� wydzielanej cze�ci.
		* \param[in] maksimum - Maksymalna obj�to�� wydzielanej cze�ci.
		* \return Zbiornik z elementami.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		Zbiornik podzielLadownie(const STyp::Objetosc& minimum, const STyp::Objetosc& maksimum);

		/**
		* \brief Metoda zwraca obj�to�� wszystkich element�w w zbiorniku.
		*
		* Metoda oblicza zaj�t� miejsce w �adowni.
		* \return Obj�to�� element�w w �adowni.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		const STyp::Objetosc& pobierzZajeteMiejsceLadowni() const;

		/**
		* \brief Metoda zwraca dost�pn� przestrze� �adowni.
		*
		* Metoda obliczaj�ca dost�pne miejsce w �adowni.
		* \return Dost�pna przestrze� �adowni.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		STyp::Objetosc pobierzDostepneMiejsceLadowni() const;

		/**
		* \brief Metoda opr�nia �adownie.
		*
		* Metoda zwraca wszystkie obiekty znajduj�ce si� w �adowni. Pozostawia �adownie pust�.
		* \return Zbiornik zawieraj�cy obiekty.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		Zbiornik oproznijLadownie();

		/**
		* \brief Metoda zapisuj�ca.
		*
		* Metoda s�u��ca do zapisu danych do w�z�a xml podanego jako parametr.
		* \param[out] wezel - W�ze� do kt�rego s� zapisywane dane.
		* \return Zwracana jest warto�� true, je�eli zapisano obiekt poprawnie. False, je�eli zapis si� nie powi�d�.
		* \warning Je�eli zwr�cono warto�� false w�ze� przekazany jako parametr nie jest zmodyfokowany.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		bool zapisz(XmlBO::ElementWezla wezel) const override;

		/**
		* \brief Metoda odczytuj�ca.
		*
		* Metoda s�u��ca do odczytu danych z w�z�a xml podanego jako parametr.
		* \param[in] wezel - W�ze� z kt�rego s� odczytywane dane.
		* \return Zwracana jest warto�� true, je�eli odczytano obiekt poprawnie. False, je�eli odczyt si� nie powi�d�.
		* \warning Metoda nie modyfikuje w�z�a.
		* \warning Je�eli metoda zwr�ci warto�� false, obiekt mo�e znajdowa� si� w stanie nieustalonym. Nie jest zalecane u�ywanie takiego obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		*/
		std::string napis()const override;

	protected:

		/**
		* \brief Metoda przeliczaj�ca zaj�te miejsce w �adowni.
		*
		* Metoda przeliczaj�ca zaj�te miejsce w �adowni.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		void przeliczZajeteMiejsceLadowni();

		/**
		* \brief Metoda pobieraj�ca mas� obiekt�w znajduj�cych si� w �adowni.
		*
		* Metoda wyliczaj�ca mas� obiekt�w w �adowni.
		* \return Masa obiekt�w w �adowni.
		* \author Daniel Wojdak
		* \version 1
		* \date 24-07-2013
		*/
		STyp::Masa pobierzMaseZawartosciLadowni()const;

		Zbiornik obiekty_; /// Lista element�w w �adowni.
		STyp::Objetosc zajete_; /// Zaj�te miejsce.

	private:
		const LadowniaInfo& ladowniaInfo_; /// Referencja do obiektu opisuj�cego.
	};
}
