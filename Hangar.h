#pragma once
#include "Serializacja.h"
#include "Logger\LoggerInterface.h"
#include "PodstawoweParametry.h"
#include "ListaObiektow.hpp"

namespace SpEx{
	class HangarInfo;
	class Statek;
	/**
	* \brief Klasa reprezentuj�ca hangar.
	*
	* Klasa reprezentuje hangar statku. Mo�na w nim przewozi� inne statki.
	* \author Daniel Wojdak
	* \version 3
	* \date 16-07-2014
	*/
	class Hangar :
		virtual public PodstawoweParametry,
		virtual public SLog::LoggerInterface,
		virtual public Serializacja
	{
	public:

		typedef Statek Item;
		typedef ListaObiektow< Item > Zbiornik;
		typedef std::vector < STyp::Identyfikator > ListaKluczy;

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] ilosc - Ilo�� tworzonych obiekt�w.
		* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
		* \param[in] hangarInfo - Referencja do obiektu opisuj�cego.
		* \author Daniel Wojdak
		* \version 3
		* \date 16-07-2014
		*/
		Hangar(const STyp::Ilosc& ilosc, const STyp::Identyfikator& identyfikatorPlanety, const HangarInfo& hangarInfo);

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] podstawoweParametry - Podstawowe parametry tworzonych obiekt�w.
		* \param[in] hangarInfo - Referencja do obiektu opisuj�cego.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		Hangar(const PodstawoweParametry& podstawoweParametry, const HangarInfo& hangarInfo);

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~Hangar() = default;

		/**
		* \brief Metoda wyliczaj�ca procent wolnego miejsca.
		*
		* Metoda obliczaj�ca procent wolnego miejsca.
		* \return Procentowa warto�� wolnego miejsca w hangarze.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		STyp::Fluktuacja wolneMiejsceHangaru() const;

		/**
		* \brief Metoda dodaj�ca statek do hangaru
		*
		* Metoda dodaj�ca statek do hangaru.
		* \param[in] obiekt - Statek dodawany do hangaru.
		* \return true je�eli dodano obiekt, false w przeciwnym wypadku.
		* \remark Metoda tworzy kopie elementu. Metoda tranzakcyjna.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		bool dodajStatekDoHangaru(const Item& obiekt);

		/**
		* \brief Metoda dodaj�ca statek do hangaru
		*
		* Metoda dodaj�ca statek do hangaru.
		* \param[in] obiekt - Statek dodawany do hangaru.
		* \return true je�eli dodano obiekt, false w przeciwnym wypadku.
		* \remark Metoda nie tworzy kopii elementu. Metoda tranzakcyjna.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		bool dodajStatekDoHangaru(std::shared_ptr<Item> obiekt);

		/**
		* \brief Metoda wylicza powierzchni� maksymaln� hangaru.
		*
		* Metoda oblicza maksymaln� powierzchni� hangaru.
		* \return Powierzchnia maksymalna hangaru.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		virtual STyp::Powierzchnia pobierzPojemnoscMaksymalnaHangaru() const;

		/**
		* \brief Metoda pobieraj�ca powierzchni� jednostkow�.
		*
		* Metoda obliczaj�ca powierzchnie jednostkow�.
		* \return Obj�to�� jednostkowa hangaru.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		STyp::Powierzchnia pobierzPojemnoscJednostkowaHangaru() const;

		/**
		* \brief Metoda ��czy obiekty hangaru.
		*
		* Metoda przenosi obiekty z hangaru przekazanej przez parametr do obiektu docelowego.
		* \param[in] hangar - Hangar �r�d�owy.
		* \return true je�eli uda si� przenie��, false w przeciwnym wypadku.
		* \remark Metoda tranzakcyjna.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		bool polaczHangar(Hangar& hangar);

		/**
		* \brief Metoda ��czy obiekty hangaru.
		*
		* Metoda przenosi obiekty z hangaru przekazanej przez parametr do obiektu docelowego.
		* \param[in] zbiornik - Hangar �r�d�owy.
		* \return true je�eli uda si� przenie��, false w przeciwnym wypadku.
		* \remark Metoda tranzakcyjna.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		bool polaczHangar(Zbiornik zbiornik);

		/**
		* \brief Metoda pobiera ilo�� obiekt�w o podanym kluczu.
		*
		* Metoda pobieraj�ca ilo�� obiekt�w o kluczu podanym w parametrze.
		* \param[in] klucz - Klucz identyfikuj�cy obiekt.
		* \return Ilo�� obiekt�w o podanym kluczu znajduj�ca si� w hangarze.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		STyp::Ilosc pobierzIloscStatkow(const STyp::Identyfikator& klucz) const;

		/**
		* \brief Metoda wyjmuje z hangaru statek o podanym kluczu i podanej ilo�ci
		*
		* Metoda wyjmuje z hangaru statek o kluczu i ilo�ci podanej w parametrze. 
		* \param[in] klucz - Klucz identyfikuj�cy obiekt.
		* \param[in] ilosc - Ilo�� obiekt�w o podanym kluczu.
		* \return Wska�nik na wyj�ty obiekt. nullptr je�eli wystapi� b�ad.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		std::shared_ptr<Item> wyjmijStatek(const STyp::Identyfikator& klucz, const STyp::Ilosc& ilosc);

		/**
		* \brief Metoda zwraca list� kluczy obiekt�w.
		*
		* Metoda generuje list� kluczy wszystkich obiekt�w znajduj�cych si� w hangarze.
		* \return Lista kluczy obiekt�w znajduj�cych sie w hangarze.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		ListaKluczy pobierzListeIdentyfikatorowStatkow() const;

		/**
		* \brief Metoda zwraca list� obiekt�w znajduj�cych si� w hangarze.
		*
		* Metoda zwraca zawarto�� hangaru.
		* \return Lista obiekt�w znajduj�cych si� w hangarze.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		const Zbiornik& pobierzPrzewozoneStatki() const;

		/**
		* \brief Metoda dzieli hangar.
		*
		* Metoda dzieli hangar w taki spos�b, aby obj�to�� odzielonej cz�ci hangaru zawiera� si� w przedziale \<minimum,maksimum\>.
		* \param[in] minimum - Minimalna obj�to�� wydzielanej cze�ci.
		* \param[in] maksimum - Maksymalna obj�to�� wydzielanej cze�ci.
		* \return Zbiornik z elementami.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		Zbiornik podzielHangar(const STyp::Powierzchnia& minimum, const STyp::Powierzchnia& maksimum);

		/**
		* \brief Metoda zwraca powierzchni� wszystkich element�w w hangarze.
		*
		* Metoda obliczaj�ca zaj�t� powierzchni� hangaru.
		* \return Powierzchnia element�w w hangarze.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		const STyp::Powierzchnia& pobierzZajeteMiejsceHangaru() const;

		/**
		* \brief Metoda zwraca dost�pn� powierzchni� hangaru.
		*
		* Metoda oblicza dost�pna powierzchni� hangaru.
		* \return Dost�pna powierzchnia hangaru.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		STyp::Powierzchnia pobierzDostepneMiejsceHangaru() const;

		/**
		* \brief Metoda opr�nia hangar.
		*
		* Metoda zwraca wszystkie obiekty znajduj�ce si� w hangarze. Pozostawia hangar pusty.
		* \return Zbiornik zawieraj�cy obiekty.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		Zbiornik oproznijHangar();

		/**
		* \brief Metoda zapisuj�ca.
		*
		* Metoda s�u��ca do zapisu danych do w�z�a xml podanego jako parametr.
		* \param[out] wezel - W�ze� do kt�rego s� zapisywane dane.
		* \return Zwracana jest warto�� true, je�eli zapisano obiekt poprawnie. False, je�eli zapis si� nie powi�d�.
		* \warning Je�eli zwr�cono warto�� false w�ze� przekazany jako parametr nie jest zmodyfokowany.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
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
		* \version 2
		* \date 11-03-2014
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		*/
		std::string napis()const override;

	protected:

		/**
		* \brief Metoda przeliczaj�ca zaj�te miejsce w hangarze.
		*
		* Metoda przelicza zaj�t� powierzchni� w hangarze.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		void przeliczZajeteMiejsceHangaru();
		
		/**
		* \brief Metoda obliczaj�ca mas� obiekt�w w hangarze.
		*
		* Metoda oblicza mas� obiekt�w znajduj�cych si� w hangarze.
		* \return Masa zawarto�ci �adowni.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		STyp::Masa pobierzMaseZawartosciHangaru()const;

		Zbiornik obiekty_; /// Lista element�w w hangarze.
		STyp::Powierzchnia zajete_ = 0; /// Zaj�te miejsce.

	private:

		const HangarInfo& hangarInfo_; /// Referencja do obiektu opisowego.
	};
}
