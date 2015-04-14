#pragma once
#include "Serializacja.h"
#include "Logger\LoggerInterface.h"
#include "PodstawoweParametry.h"
#include "ListaObiektow.hpp"

namespace SpEx{
	class HangarInfo;
	class Statek;
	/**
	* \brief Klasa reprezentuj¹ca hangar.
	*
	* Klasa reprezentuje hangar statku. Mo¿na w nim przewoziæ inne statki.
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
		* \param[in] ilosc - Iloœæ tworzonych obiektów.
		* \param[in] identyfikatorPlanety - Identyfikator planety rodzica obiektu.
		* \param[in] hangarInfo - Referencja do obiektu opisuj¹cego.
		* \author Daniel Wojdak
		* \version 3
		* \date 16-07-2014
		*/
		Hangar(const STyp::Ilosc& ilosc, const STyp::Identyfikator& identyfikatorPlanety, const HangarInfo& hangarInfo);

		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] podstawoweParametry - Podstawowe parametry tworzonych obiektów.
		* \param[in] hangarInfo - Referencja do obiektu opisuj¹cego.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		Hangar(const PodstawoweParametry& podstawoweParametry, const HangarInfo& hangarInfo);

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~Hangar() = default;

		/**
		* \brief Metoda wyliczaj¹ca procent wolnego miejsca.
		*
		* Metoda obliczaj¹ca procent wolnego miejsca.
		* \return Procentowa wartoœæ wolnego miejsca w hangarze.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		STyp::Fluktuacja wolneMiejsceHangaru() const;

		/**
		* \brief Metoda dodaj¹ca statek do hangaru
		*
		* Metoda dodaj¹ca statek do hangaru.
		* \param[in] obiekt - Statek dodawany do hangaru.
		* \return true je¿eli dodano obiekt, false w przeciwnym wypadku.
		* \remark Metoda tworzy kopie elementu. Metoda tranzakcyjna.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		bool dodajStatekDoHangaru(const Item& obiekt);

		/**
		* \brief Metoda dodaj¹ca statek do hangaru
		*
		* Metoda dodaj¹ca statek do hangaru.
		* \param[in] obiekt - Statek dodawany do hangaru.
		* \return true je¿eli dodano obiekt, false w przeciwnym wypadku.
		* \remark Metoda nie tworzy kopii elementu. Metoda tranzakcyjna.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		bool dodajStatekDoHangaru(std::shared_ptr<Item> obiekt);

		/**
		* \brief Metoda wylicza powierzchniê maksymaln¹ hangaru.
		*
		* Metoda oblicza maksymaln¹ powierzchniê hangaru.
		* \return Powierzchnia maksymalna hangaru.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		virtual STyp::Powierzchnia pobierzPojemnoscMaksymalnaHangaru() const;

		/**
		* \brief Metoda pobieraj¹ca powierzchniê jednostkow¹.
		*
		* Metoda obliczaj¹ca powierzchnie jednostkow¹.
		* \return Objêtoœæ jednostkowa hangaru.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		STyp::Powierzchnia pobierzPojemnoscJednostkowaHangaru() const;

		/**
		* \brief Metoda ³¹czy obiekty hangaru.
		*
		* Metoda przenosi obiekty z hangaru przekazanej przez parametr do obiektu docelowego.
		* \param[in] hangar - Hangar Ÿród³owy.
		* \return true je¿eli uda siê przenieœæ, false w przeciwnym wypadku.
		* \remark Metoda tranzakcyjna.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		bool polaczHangar(Hangar& hangar);

		/**
		* \brief Metoda ³¹czy obiekty hangaru.
		*
		* Metoda przenosi obiekty z hangaru przekazanej przez parametr do obiektu docelowego.
		* \param[in] zbiornik - Hangar Ÿród³owy.
		* \return true je¿eli uda siê przenieœæ, false w przeciwnym wypadku.
		* \remark Metoda tranzakcyjna.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		bool polaczHangar(Zbiornik zbiornik);

		/**
		* \brief Metoda pobiera iloœæ obiektów o podanym kluczu.
		*
		* Metoda pobieraj¹ca iloœæ obiektów o kluczu podanym w parametrze.
		* \param[in] klucz - Klucz identyfikuj¹cy obiekt.
		* \return Iloœæ obiektów o podanym kluczu znajduj¹ca siê w hangarze.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		STyp::Ilosc pobierzIloscStatkow(const STyp::Identyfikator& klucz) const;

		/**
		* \brief Metoda wyjmuje z hangaru statek o podanym kluczu i podanej iloœci
		*
		* Metoda wyjmuje z hangaru statek o kluczu i iloœci podanej w parametrze. 
		* \param[in] klucz - Klucz identyfikuj¹cy obiekt.
		* \param[in] ilosc - Iloœæ obiektów o podanym kluczu.
		* \return WskaŸnik na wyjêty obiekt. nullptr je¿eli wystapi³ b³ad.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		std::shared_ptr<Item> wyjmijStatek(const STyp::Identyfikator& klucz, const STyp::Ilosc& ilosc);

		/**
		* \brief Metoda zwraca listê kluczy obiektów.
		*
		* Metoda generuje listê kluczy wszystkich obiektów znajduj¹cych siê w hangarze.
		* \return Lista kluczy obiektów znajduj¹cych sie w hangarze.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		ListaKluczy pobierzListeIdentyfikatorowStatkow() const;

		/**
		* \brief Metoda zwraca listê obiektów znajduj¹cych siê w hangarze.
		*
		* Metoda zwraca zawartoœæ hangaru.
		* \return Lista obiektów znajduj¹cych siê w hangarze.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		const Zbiornik& pobierzPrzewozoneStatki() const;

		/**
		* \brief Metoda dzieli hangar.
		*
		* Metoda dzieli hangar w taki sposób, aby objêtoœæ odzielonej czêœci hangaru zawiera³ siê w przedziale \<minimum,maksimum\>.
		* \param[in] minimum - Minimalna objêtoœæ wydzielanej czeœci.
		* \param[in] maksimum - Maksymalna objêtoœæ wydzielanej czeœci.
		* \return Zbiornik z elementami.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		Zbiornik podzielHangar(const STyp::Powierzchnia& minimum, const STyp::Powierzchnia& maksimum);

		/**
		* \brief Metoda zwraca powierzchniê wszystkich elementów w hangarze.
		*
		* Metoda obliczaj¹ca zajêt¹ powierzchniê hangaru.
		* \return Powierzchnia elementów w hangarze.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		const STyp::Powierzchnia& pobierzZajeteMiejsceHangaru() const;

		/**
		* \brief Metoda zwraca dostêpn¹ powierzchniê hangaru.
		*
		* Metoda oblicza dostêpna powierzchniê hangaru.
		* \return Dostêpna powierzchnia hangaru.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		STyp::Powierzchnia pobierzDostepneMiejsceHangaru() const;

		/**
		* \brief Metoda opró¿nia hangar.
		*
		* Metoda zwraca wszystkie obiekty znajduj¹ce siê w hangarze. Pozostawia hangar pusty.
		* \return Zbiornik zawieraj¹cy obiekty.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		Zbiornik oproznijHangar();

		/**
		* \brief Metoda zapisuj¹ca.
		*
		* Metoda s³u¿¹ca do zapisu danych do wêz³a xml podanego jako parametr.
		* \param[out] wezel - Wêze³ do którego s¹ zapisywane dane.
		* \return Zwracana jest wartoœæ true, je¿eli zapisano obiekt poprawnie. False, je¿eli zapis siê nie powiód³.
		* \warning Je¿eli zwrócono wartoœæ false wêze³ przekazany jako parametr nie jest zmodyfokowany.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
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
		* \version 2
		* \date 11-03-2014
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		*/
		std::string napis()const override;

	protected:

		/**
		* \brief Metoda przeliczaj¹ca zajête miejsce w hangarze.
		*
		* Metoda przelicza zajêt¹ powierzchniê w hangarze.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		void przeliczZajeteMiejsceHangaru();
		
		/**
		* \brief Metoda obliczaj¹ca masê obiektów w hangarze.
		*
		* Metoda oblicza masê obiektów znajduj¹cych siê w hangarze.
		* \return Masa zawartoœci ³adowni.
		* \author Daniel Wojdak
		* \version 2
		* \date 11-03-2014
		*/
		STyp::Masa pobierzMaseZawartosciHangaru()const;

		Zbiornik obiekty_; /// Lista elementów w hangarze.
		STyp::Powierzchnia zajete_ = 0; /// Zajête miejsce.

	private:

		const HangarInfo& hangarInfo_; /// Referencja do obiektu opisowego.
	};
}
