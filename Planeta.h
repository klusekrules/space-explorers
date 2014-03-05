#pragma once
#include "Logger\LoggerInterface.h"
#include <map>
#include <memory>
#include "Budynek.h"
#include "Statek.h"
#include "Technologia.h"
#include "Surowce.h"
#include "NiepoprawnaIloscObiektow.h"
#include "Flota.h"
#include "Licznik.h"
#include "Obrona.h"

namespace SpEx{

	/**
	* \brief Klasa reprezentuj�ca planet�.
	*
	* Klasa reprezentuj�ca planet�.
	* \author Daniel Wojdak
	* \version 1
	* \date 26-07-2013
	*/
	class Planeta :
		virtual public SLog::LoggerInterface,
		virtual public Serializacja
	{
		friend class Gra;
		friend class Uzytkownik;
	public:
		typedef STyp::Identyfikator Indeks;
		typedef std::map< Indeks, std::shared_ptr< Obiekt > > ListaObiektow;
		typedef std::map< Indeks, std::shared_ptr< Budynek > > ListaBudynkow;
		typedef std::map< Indeks, std::shared_ptr< Technologia > > ListaTechnologii;
		typedef std::map< Indeks, std::shared_ptr< Statek > > ListaStatkow;
		typedef std::map< Indeks, std::shared_ptr< Obrona > > ListaObrona;
		typedef std::map< Indeks, std::shared_ptr< Surowce > > ListaSurowcow;
		typedef std::map< STyp::Identyfikator, std::shared_ptr< Flota > > ListaFlot;
		typedef std::map< Indeks, STyp::Ilosc > ListaZasobow;

		/**
		* \brief Konstruktor.
		*
		* \param[in] identyfikator - Identyfikator planety.
		* \param[in] identyfikatorUkladu - Numer identyfikuj�cy uk�ad s�oneczny
		*/
		Planeta(const STyp::Identyfikator& identyfikator, const STyp::Identyfikator& identyfikatorUkladu);

		/**
		* \brief Destruktor.
		*/
		virtual ~Planeta(void) = default;
		
		const STyp::Identyfikator& pobierzIdentyfikator()const;

		/**
		* \brief Metoda pobiera ilo�� r�nych typ�w obiekt�w dost�pnych na planecie.
		*
		* \return Ilo�� typ�w obiekt�w na planecie.
		*/
		STyp::Ilosc pobierzIloscTypowObiektow()const;

		/**
		* \brief Metoda pobiera obiekt o podanym identyfikatorze.
		*
		* Metoda pobiera z planety obiekt o podanym identyfikatorze.
		* \param[in] identyfikator - Identyfikator obiektu.
		* \return Referencja do obiektu.
		*/
		const Obiekt& pobierzObiekt(const Indeks& identyfikator) const;
		
		/**
		* \brief Metoda pobiera statek o podanym identyfikatorze.
		*
		* Metoda pobiera z planety statek o podanym identyfikatorze.
		* \param[in] identyfikator - Identyfikator obiektu.
		* \return Referencja do obiektu.
		*/
		const Statek& pobierzStatek(const Indeks& identyfikator) const;

		/**
		* \brief Metoda pobiera obron� o podanym identyfikatorze.
		*
		* Metoda pobiera z planety obron� o podanym identyfikatorze.
		* \param[in] identyfikator - Identyfikator obiektu.
		* \return Referencja do obiektu.
		*/
		const Obrona& pobierzObrone(const Indeks& identyfikator) const;

		/**
		* \brief Metoda pobiera tehcnologie o podanym identyfikatorze.
		*
		* Metoda pobiera z planety tehcnologie o podanym identyfikatorze.
		* \param[in] identyfikator - Identyfikator obiektu.
		* \return Referencja do obiektu.
		*/
		const Technologia& pobierzTechnologie(const Indeks& identyfikator) const;

		/**
		* \brief Metoda pobiera budynek o podanym identyfikatorze.
		*
		* Metoda pobiera z planety budynek o podanym identyfikatorze.
		* \param[in] identyfikator - Identyfikator obiektu.
		* \return Referencja do obiektu.
		*/
		const Budynek& pobierzBudynek(const Indeks& identyfikator) const;

		/**
		* \brief Metoda buduje obiekt na planecie.
		*
		* Metoda buduje obiekt o podanym identyfikatorze i ilo�ci na planecie.
		* \param[in] identyfikator - Identyfikator obiektu.
		* \param[in] ilosc - Atrybut ilo�ci tworzonego obieku.
		* \return true je�eli uda si� wybudowa� obiekt, false w przeciwnym wypadku.
		*/
		bool wybuduj(const Indeks& identyfikator, const PodstawoweParametry& );
		bool wybuduj(const Indeks& identyfikator, const XmlBO::ElementWezla element);
		
		/**
		* \brief Metoda buduje statek na planecie.
		*
		* Metoda buduje statek na planecie.
		* \param[in] obiekt - Sprytny wska�nik na obiekt dodawany do planety.
		* \remark Metoda tworzy kopie elementu, nie zapami�tuje wska�nika przekazanego jako parametr.
		*/
		//void wybuduj(std::shared_ptr< Obiekt > obiekt);

		/**
		* \brief Metoda buduje statek na planecie.
		*
		* Metoda buduje statek na planecie.
		* \param[in] obiekt - Sprytny wska�nik na obiekt dodawany do planety.
		* \remark Je�eli nie ma �adnuych obiekt�w tego typu na planecie metoda zapisuje wska�nik, nie tworzy kopii.
		*/
		//void wybuduj(std::shared_ptr< Statek > obiekt);

		/**
		* \brief Metoda tworzy flot� na planecie.
		*
		* Metoda tworzy pusty obiekt floty na planecie i zwraca identyfikator.
		* \return Identyfikator nowo stworzonej floty.
		*/
		STyp::Identyfikator dodajFlote();

		/**
		* \brief Metoda pobiera flot�.
		*
		* Metoda pobiera sprytny wska�nik do floty o podanym identyfikatorze.
		* \param[in] identyfikator - Identyfikator floty.
		* \return Sprytny wska�nik do floty lub nullptr jezeli flota o podanym identyfikatorze nie istnieje.
		*/
		std::shared_ptr< Flota > pobierzFlote(const STyp::Identyfikator& identyfikator) const;

		/**
		* \brief Metoda usuwaj�ca flot� z planety.
		*
		* Metoda usuwa flot� z listy flot na planecie. Nie roz�adowuje jej ani nie przenosi statk�w na planete.
		* \param[in] identyfikator - Identyfikator floty do usuni�cia.
		* \return true je�eli uda�o si� usun��, false w przecwnym wypadku.
		*/
		bool usunFlote(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Metoda przeno�ci obiekt do floty.
		*
		* Metoda przenosi obiekt z planety do floty.
		* \param[in] flota - Identyfikator floty do kt�rej ma zosta� przeniesiony obiekt.
		* \param[in] obiekt - Identyfikator obiektu, kt�ry ma byc przenisiony do floty.
		* \param[in] ilosc - Ilo�� obiekt�w do przeniesienia.
		* \return true je�eli uda si� przenie�� obiekt, false w przeciwnym wypadku.
		*/
		bool przeniesDoFloty(const STyp::Identyfikator& flota, const Indeks& obiekt, const STyp::Ilosc& ilosc);

		/**
		* \brief Metoda przeno�ci obiekt do �adowni floty.
		*
		* Metoda przenosi obiekt z planety do �adowni floty.
		* \param[in] flota - Identyfikator floty do �adowni kt�rej ma zosta� przeniesiony obiekt.
		* \param[in] obiekt - Identyfikator obiektu, kt�ry ma byc przenisiony do �adowni floty.
		* \param[in] ilosc - Ilo�� obiekt�w do przeniesienia.
		* \return true je�eli uda si� przenie�� obiekt, false w przeciwnym wypadku.
		*/
		bool zaladujSurowceNaFlote(const STyp::Identyfikator& flota, const Indeks& obiekt, const STyp::Ilosc& ilosc);

		/**
		* \brief Metoda przeno�ci obiekt do hangaru floty.
		*
		* Metoda przenosi obiekt z planety do hangaru floty.
		* \param[in] flota - Identyfikator floty do hangaru kt�rej ma zosta� przeniesiony obiekt.
		* \param[in] obiekt - Identyfikator obiektu, kt�ry ma byc przenisiony do hangaru floty.
		* \param[in] ilosc - Ilo�� obiekt�w do przeniesienia.
		* \return true je�eli uda si� przenie�� obiekt, false w przeciwnym wypadku.
		*/
		bool zaladujStatekNaFlote(const STyp::Identyfikator& flota, const Indeks& obiekt, const STyp::Ilosc& ilosc);

		/**
		* \brief Metoda rozladowujaca statek.
		*
		* Metoda przenosi obiekty z �adowni na planet�.
		*/
		//void rozladujStatek(std::shared_ptr< Statek > statek); - Przeniesc do metod statku

		/**
		* \brief Metoda sprawdzaj�ca czy planeta ma w�asciciela.
		*
		* \return true je�eli obiekt posiada w�a�ciciela, false w przeciwnym przypadku.
		*/
		bool czyMaWlasciciela()const;

		/**
		* \brief Metoda pobieraj�ca nazw� planety.
		*
		* Metoda pobiera nazw� planety
		* \return Nazwa planety.
		*/
		STyp::Tekst pobierzNazwePlanety() const;

		/**
		* \brief Metoda ustawiaj�ca nazw� planety.
		*
		* Metoda ustawia nazw� planety
		* \param[in] nazwa - Nowa nazwa planety.
		*/
		void ustawNazwePlanety(const STyp::Tekst& nazwa);

		/**
		* \brief Metoda ustawia temperatur�.
		*
		* Metoda ustawiaj�ca �redni� temperatur� na planecie.
		* \param[in] temperatura - warto�� temperatury w kelwinach, jaka ma by� ustawiona w obiekcie.
		*/
		void ustawTemperature(const STyp::Temperatura& temperatura);

		/**
		* \brief Metoda ustawia �rednic�.
		*
		* Metoda ustawiaj�ca �rednic� planety.
		* \param[in] srednica - warto�� srednicy w mln km, jaka ma by� ustawiona w obiekcie.
		*/
		void ustawSrednice(const STyp::Dystans& srednica);

		/**
		* \brief Metoda ustawia odleg�o�� od �rodka uk�adu s�onecznego.
		*
		* Metoda ustawiaj�ca odleg�o�� planety od �rodka uk�adu s�onecznego.
		* \param[in] odleglosc - warto�� odleglosci w mln km, jaka ma by� ustawiona w obiekcie.
		*/
		void ustawOdlegloscOdSrodkaUkladu(const STyp::Dystans& odleglosc);

		/**
		* \brief Metoda przeliczaj�ca powierzchnie.
		*
		* Metoda przelicza powierzchni� na planecie wed�ug podanych proporcji.
		* \param[in] procentWody - procenty powierzchni b�d�cej wod�.
		* \param[in] procentUzytkowa - procent powierzchni u�ytkowej.
		* \return true je�eli argumety s� w poprawnym zakresie false w przeciwnym wypadku.
		*/
		bool wyliczPowierzchnie(const STyp::Fluktuacja& procentWody, const STyp::Fluktuacja& procentUzytkowa);

		/**
		* \brief Metoda zwracaj�ca identyfikator uk�adu rodzica.
		*
		* Metoda zwraca identyfikator uk�adu s�onecznego w kt�rym znajduje sie planeta.
		* \return Identyfikator uk�adu.
		*/
		const STyp::Identyfikator& pobierzIdUkladu() const;

		/**
		* \brief Metoda czy�ci zawarto�� planety.
		*
		* Metoda czy�ci zawarto�� planety. Usuwa tak�e powi�zanie z u�ytkownikiem je�eli takowe istnieje oraz zalogowany jest u�ytkownik kt�ry jest przypisany do planety.
		* \todo Metoda do zmiany. Usuni�cie sprawdzania warunku tego samego u�ytkownika. Przeniesienie tego w inne miejsce.
		*/
		void wyczyscZawartoscPlanety();

		/**
		* \brief Metoda zwracaj�ca poziom obiektu.
		*
		* Metoda zwraca nawy�szy poziom obiektu o podanym identyfikatorze.
		* \param[in] identyfikator - Numer identyfikuj�cy obiekt.
		* \return Poziom obiektu lub 0 je�eli nie znaleziono obiektu.
		*/
		STyp::Poziom pobierzPoziomObiektu(const Indeks& identyfikator) const;

		/**
		* \brief Metoda zwracaj�ca ilo�� obiektu.
		*
		* Metoda zwraca ilo��obiektu o podanym indeksie.
		* \param[in] indeks - Indeks obiekt.
		* \return Ilo�� obiektu lub 0 je�eli nie znaleziono obiektu.
		*/
		STyp::Ilosc pobierzIloscObiektu(const Indeks& indeks) const;

		/**
		* \brief Metoda zapisuj�ca.
		*
		* Metoda s�u��ca do zapisu danych do w�z�a xml podanego jako parametr.
		* \param[out] wezel - W�ze� do kt�rego s� zapisywane dane.
		* \return Zwracana jest warto�� true, je�eli zapisano obiekt poprawnie. False, je�eli zapis si� nie powi�d�.
		* \warning Je�eli zwr�cono warto�� false w�ze� przekazany jako parametr nie jest zmodyfokowany.
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
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		*/
		std::string napis() const override;

		/**
		* \brief Metoda dodaj�ca Budynek do planety.
		*
		* Metoda dodaje Budynek do planety. Nie tworzy kopii. Sprawdza czy istnieje budynek o takim samym identyfikatorze.
		* \param[in] obiekt - Sprytny wska�nik na dodawany obiekt.
		* \return true je�eli uda si� doda� obiekt, fasle w przeciwnym wypadku.
		*/
		bool dodajObiekt(std::shared_ptr< Budynek > obiekt);

		/**
		* \brief Metoda dodaj�ca Obron� do planety.
		*
		* Metoda dodaje Obron� do planety. Nie tworzy kopii. Sprawdza czy istnieje obrona o takim samym identyfikatorze.
		* \param[in] obiekt - Sprytny wska�nik na dodawany obiekt.
		* \return true je�eli uda si� doda� obiekt, fasle w przeciwnym wypadku.
		*/
		bool dodajObiekt(std::shared_ptr< Obrona > obiekt);

		/**
		* \brief Metoda dodaj�ca Statek do planety.
		*
		* Metoda dodaje Statek do planety. Nie tworzy kopii. Sprawdza czy istnieje budynek o takim samym identyfikatorze.
		* \param[in] obiekt - Sprytny wska�nik na dodawany obiekt.
		* \return true je�eli uda si� doda� obiekt, fasle w przeciwnym wypadku.
		*/
		bool dodajObiekt(std::shared_ptr< Statek > obiekt);

		/**
		* \brief Metoda dodaj�ca Technologie do planety.
		*
		* Metoda dodaje Technologie do planety. Nie tworzy kopii. Sprawdza czy istnieje budynek o takim samym identyfikatorze.
		* \param[in] obiekt - Sprytny wska�nik na dodawany obiekt.
		* \return true je�eli uda si� doda� obiekt, fasle w przeciwnym wypadku.
		*/
		bool dodajObiekt(std::shared_ptr< Technologia > obiekt);

		/**
		* \brief Metoda dodaj�ca Surowce do planety.
		*
		* Metoda dodaje Surowce do planety. Nie tworzy kopii. Sprawdza czy istnieje budynek o takim samym identyfikatorze.
		* \param[in] obiekt - Sprytny wska�nik na dodawany obiekt.
		* \return true je�eli uda si� doda� obiekt, fasle w przeciwnym wypadku.
		*/
		bool dodajObiekt(std::shared_ptr< Surowce > obiekt);
	
	private:

		/**
		* \brief Metoda ustawia w�a�ciciela planety.
		*
		* Metoda zamienia bierz�cego w�a�ciciela na podanego w parametrze.
		* \param[in] uzytkownik - Wska�nik na u�ytkownika.
		*/
		void ustawWlasciciela(Uzytkownik* uzytkownik);

		/**
		* \brief Metoda pobiera w�a�ciciela.
		*
		*\return Wska�nika na w�a�ciciela.
		*/
		Uzytkownik* pobierzWlasciciela() const;

		Licznik licznikIdentyfikatorowFloty_; /// Licznik identyfikator�w flot.
		Uzytkownik* wlasciciel_; /// W�a�ciciel planety.

		ListaSurowcow listaSurowcow_; /// Lista surowc�w planety.
		ListaStatkow listaStatkow_; /// Lista statk�w planety
		ListaObrona listaObrona_; /// Lista statk�w planety
		ListaTechnologii listaTechnologii_; /// Lista tehcnologii planety.
		ListaBudynkow listaBudynkow_; /// Lista budynk�w planety.
		ListaObiektow listaObiektow_; /// Lista wszystkich obiekt�w planety.
		ListaFlot listaFlot_; /// Lista flot planety.

		/* Lista parametr�w planety */
		STyp::Dystans srednicaPlanety_; /// Atrybut przechowuje informacje o �rednicy planety.
		STyp::Dystans odlegloscOdSlonca_; /// Atrybut przechowuje informacje o odleg�o�ci planety od centrum uk�adu s�onecznego.
		//Predkosc predkoscKatowaPlanety_ ; /// Atrybut przechowuje informacje o pr�dko�ci obiegu planety woko�o s�o�ca.
		//Fluktuacja naslonecznieniePlanety_; /// Atrybut przechowuj�cy informacje o nas�onecznieniu planety.
		//Fluktuacja wietrznoscPlanety_; /// Atrybut przechowuj�cy informacje o nat�eniu wiatr�w na planecie.
		STyp::Temperatura temperaturaPlanety_; /// Atrybut przechowuj�cy informacje o �redniej temperaturze planety.
		STyp::Powierzchnia calkowitaPowierzchniaPlanety_; /// Atrybut przehcowuj�cy informacje o ca�kowitej powierzchni planety.
		STyp::Powierzchnia powierzchniaZajetaPrzezWode_; /// Atrybut przechowuj�cy informacje o powierzchni planety zaj�tej przez wod�.
		STyp::Powierzchnia powierzchniaLadow_; /// Atrybut przechowuj�cy informacje o powierzchni planety zaj�tej przez l�dy.
		STyp::Powierzchnia powierzchniaUzytkowaLadow_; /// Atrybut przechowuj�cy informacje o powierzchni u�ytkowej planety.
		ListaZasobow dostepneZasobyPlanety_; /// Lista zasob�w jakie mo�na wydoby� na planecie.
		STyp::Tekst nazwaPlanety_; /// Nazwa planety.

		STyp::Identyfikator identyfikator_;
		STyp::Identyfikator idUkladu_; /// Uk�ad s�oneczny w kt�rym znajduje si� planeta.
		STyp::Tekst idUzytkownika_; /// Nazwa u�ytkownika przypisanego do planety.
	};
}
