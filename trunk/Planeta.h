#pragma once
#include "Logger\LoggerInterface.h"
#include <map>
#include <memory>
#include "Budynek.h"
#include "Statek.h"
#include "Technologia.h"
#include "Surowce.h"
#include "Flota.h"
#include "Licznik.h"
#include "Obrona.h"

namespace SpEx{

	/**
	* \brief Klasa reprezentuj�ca planet�.
	*
	* Klasa reprezentuj�ca planet�.
	* \author Daniel Wojdak
	* \version 2
	* \date 14-07-2014
	*/
	class Planeta :
		virtual public SLog::LoggerInterface,
		virtual public Serializacja
	{
		friend class Gra;
		friend class Uzytkownik;
	public:
		typedef STyp::Identyfikator Indeks;
		typedef std::map< Indeks, Obiekt::SharedPtr > ListaObiektow;
		typedef std::map< Indeks, Budynek::SharedPtr > ListaBudynkow;
		typedef std::map< Indeks, Technologia::SharedPtr > ListaTechnologii;
		typedef std::map< Indeks, Statek::SharedPtr > ListaStatkow;
		typedef std::map< Indeks, Obrona::SharedPtr > ListaObrona;
		typedef std::map< Indeks, Surowce::SharedPtr > ListaSurowcow;
		typedef std::map< Indeks, Flota::SharedPtr > ListaFlot;
		
		/**
		* \brief Konstruktor.
		*
		* Konstruktor.
		* \param[in] identyfikator - Identyfikator planety.
		* \param[in] identyfikatorUkladu - Numer identyfikuj�cy uk�ad s�oneczny
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		Planeta(const STyp::Identyfikator& identyfikator, const STyp::Identyfikator& identyfikatorUkladu);

		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~Planeta(void) = default;
		
		/**
		* \brief Metoda pobieraj�ca identyfikator.
		*
		* Metoda pobiera identyfikator obiektu.
		* \return Identyfikator obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		const STyp::Identyfikator& pobierzIdentyfikator()const;

		/**
		* \brief Metoda pobiera ilo�� r�nych typ�w obiekt�w dost�pnych na planecie.
		*
		* \return Ilo�� typ�w obiekt�w na planecie.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		STyp::Ilosc pobierzIloscTypowObiektow()const;

		/**
		* \brief Metoda pobiera obiekt o podanym identyfikatorze.
		*
		* Metoda pobiera z planety obiekt o podanym identyfikatorze.
		* \param[in] identyfikator - Identyfikator obiektu.
		* \return Wska�nik obiektu lub nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		template <class T>
		typename T::ConstSharedPtr pobierzObiektJesliIstnieje(const Indeks& identyfikator) const{
			return znajdzObiekt<T,NOTHROW>(identyfikator);
		}
		
		template <class T>
		typename T::SharedPtr pobierzObiektJesliIstnieje(const Indeks& identyfikator){
			return znajdzObiekt<T, NOTHROW>(identyfikator);
		}
		/**
		* \brief Metoda pobiera obiekt o podanym identyfikatorze.
		*
		* Metoda pobiera z planety obiekt o podanym identyfikatorze.
		* \param[in] identyfikator - Identyfikator obiektu.
		* \return Referencja do obiektu. Je�eli obiekt nie zostanie znaleziony jest wyrzucany wyj�tek.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		template <class T>
		const T& pobierzObiekt(const Indeks& identyfikator) const{
			return *(znajdzObiekt<T, THROW>(identyfikator));
		}
		
		/**
		* \brief Metoda pobiera list� surowc�w.
		*
		* Metoda pobiera z planety list� surowc�w.
		* \return Referencja do listy surowc�w.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		const ListaSurowcow& pobierzSurowce()const;
		
		/**
		* \brief Metoda buduje obiekt na planecie.
		*
		* Metoda buduje obiekt o podanym identyfikatorze na planecie.
		* \param[in] identyfikator - Identyfikator obiektu.
		* \param[in] parametr - Parametr podstawowy tworzonego obieku.
		* \return true je�eli uda si� wybudowa� obiekt, false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		bool wybuduj(const Indeks& identyfikator, const PodstawoweParametry& parametr);

		/**
		* \brief Metoda buduje obiekt na planecie.
		*
		* Metoda buduje obiekt o podanym identyfikatorze na planecie.
		* \param[in] identyfikator - Identyfikator obiektu.
		* \param[in] element - W�ze� opisuj�cy tworzony obiek.
		* \return true je�eli uda si� wybudowa� obiekt, false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		bool wybuduj(const Indeks& identyfikator, const XmlBO::ElementWezla element);
		
		/**
		* \brief Metoda tworzy flot� na planecie.
		*
		* Metoda tworzy pusty obiekt floty na planecie i zwraca identyfikator.
		* \return Identyfikator nowo stworzonej floty.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		Indeks dodajFlote();

		/**
		* \brief Metoda usuwaj�ca flot� z planety.
		*
		* Metoda usuwa flot� z listy flot na planecie. Nie roz�adowuje jej ani nie przenosi statk�w na planete.
		* \param[in] identyfikator - Identyfikator floty do usuni�cia.
		* \return true je�eli uda�o si� usun��, false w przecwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		bool usunFlote(const Indeks& identyfikator);

		/**
		* \brief Metoda przeno�ci obiekt do floty.
		*
		* Metoda przenosi obiekt z planety do floty.
		* \param[in] flota - Identyfikator floty do kt�rej ma zosta� przeniesiony obiekt.
		* \param[in] obiekt - Identyfikator obiektu, kt�ry ma byc przenisiony do floty.
		* \param[in] ilosc - Ilo�� obiekt�w do przeniesienia.
		* \return true je�eli uda si� przenie�� obiekt, false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		bool przeniesDoFloty(const Indeks& flota, const Indeks& obiekt, const STyp::Ilosc& ilosc);

		/**
		* \brief Metoda przeno�ci obiekt do �adowni floty.
		*
		* Metoda przenosi obiekt z planety do �adowni floty.
		* \param[in] flota - Identyfikator floty do �adowni kt�rej ma zosta� przeniesiony obiekt.
		* \param[in] obiekt - Identyfikator obiektu, kt�ry ma byc przenisiony do �adowni floty.
		* \param[in] ilosc - Ilo�� obiekt�w do przeniesienia.
		* \return true je�eli uda si� przenie�� obiekt, false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		bool zaladujSurowceNaFlote(const Indeks& flota, const Indeks& obiekt, const STyp::Ilosc& ilosc);

		/**
		* \brief Metoda przeno�ci obiekt do hangaru floty.
		*
		* Metoda przenosi obiekt z planety do hangaru floty.
		* \param[in] flota - Identyfikator floty do hangaru kt�rej ma zosta� przeniesiony obiekt.
		* \param[in] obiekt - Identyfikator obiektu, kt�ry ma byc przenisiony do hangaru floty.
		* \param[in] ilosc - Ilo�� obiekt�w do przeniesienia.
		* \return true je�eli uda si� przenie�� obiekt, false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		bool zaladujStatekNaFlote(const Indeks& flota, const Indeks& obiekt, const STyp::Ilosc& ilosc);

		/**
		* \brief Metoda rozladowujaca statek.
		*
		* Metoda przenosi obiekty z �adowni na planet�.
		* \param[in] statek - Statek do roz�adowania
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		* \todo Metoda oznaczona do przeniesienia do klasy Statek.
		*/
		void rozladujStatek(Statek::SharedPtr statek);

		/**
		* \brief Metoda sprawdzaj�ca czy planeta ma w�asciciela.
		*
		* \return true je�eli obiekt posiada w�a�ciciela, false w przeciwnym przypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		bool czyMaWlasciciela()const;

		/**
		* \brief Metoda pobieraj�ca nazw� planety.
		*
		* Metoda pobiera nazw� planety
		* \return Nazwa planety.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		STyp::Tekst pobierzNazwePlanety() const;

		/**
		* \brief Metoda ustawiaj�ca nazw� planety.
		*
		* Metoda ustawia nazw� planety
		* \param[in] nazwa - Nowa nazwa planety.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		void ustawNazwePlanety(const STyp::Tekst& nazwa);

		/**
		* \brief Metoda ustawia temperatur�.
		*
		* Metoda ustawiaj�ca �redni� temperatur� na planecie.
		* \param[in] temperatura - warto�� temperatury w kelwinach, jaka ma by� ustawiona w obiekcie.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		void ustawTemperature(const STyp::Temperatura& temperatura);

		/**
		* \brief Metoda ustawia �rednic�.
		*
		* Metoda ustawiaj�ca �rednic� planety.
		* \param[in] srednica - warto�� srednicy w mln km, jaka ma by� ustawiona w obiekcie.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		void ustawSrednice(const STyp::Dystans& srednica);

		/**
		* \brief Metoda ustawia odleg�o�� od �rodka uk�adu s�onecznego.
		*
		* Metoda ustawiaj�ca odleg�o�� planety od �rodka uk�adu s�onecznego.
		* \param[in] odleglosc - warto�� odleglosci w mln km, jaka ma by� ustawiona w obiekcie.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		void ustawOdlegloscOdSrodkaUkladu(const STyp::Dystans& odleglosc);

		/**
		* \brief Metoda przeliczaj�ca powierzchnie.
		*
		* Metoda przelicza powierzchni� na planecie wed�ug podanych proporcji.
		* \param[in] procentWody - procenty powierzchni b�d�cej wod�.
		* \param[in] procentUzytkowa - procent powierzchni u�ytkowej.
		* \return true je�eli argumety s� w poprawnym zakresie false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		bool wyliczPowierzchnie(const STyp::Fluktuacja& procentWody, const STyp::Fluktuacja& procentUzytkowa);

		/**
		* \brief Metoda zwracaj�ca identyfikator uk�adu rodzica.
		*
		* Metoda zwraca identyfikator uk�adu s�onecznego w kt�rym znajduje sie planeta.
		* \return Identyfikator uk�adu.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		const STyp::Identyfikator& pobierzIdUkladu() const;

		/**
		* \brief Metoda czy�ci zawarto�� planety.
		*
		* Metoda czy�ci zawarto�� planety. Usuwa tak�e powi�zanie z u�ytkownikiem je�eli takowe istnieje oraz zalogowany jest u�ytkownik kt�ry jest przypisany do planety.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		void wyczyscZawartoscPlanety();

		/**
		* \brief Metoda od��czaj�ca planet�.
		*
		* Metoda od��cza planet� od w�a�ciciela.
		* \return Warto�� true, je�eli od��czono w�a�ciciela lub nie ma w�a�ciciela, warto�� false, je�eli nie uda�o si� od��czy� w�a�ciciela.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		bool odepnijPlanete();

		/**
		* \brief Metoda zwracaj�ca poziom obiektu.
		*
		* Metoda zwraca nawy�szy poziom obiektu o podanym identyfikatorze.
		* \param[in] identyfikator - Numer identyfikuj�cy obiekt.
		* \return Poziom obiektu lub 0 je�eli nie znaleziono obiektu.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		STyp::Poziom pobierzPoziomObiektu(const Indeks& identyfikator) const;

		/**
		* \brief Metoda zwracaj�ca ilo�� obiektu.
		*
		* Metoda zwraca ilo��obiektu o podanym indeksie.
		* \param[in] indeks - Indeks obiekt.
		* \return Ilo�� obiektu lub 0 je�eli nie znaleziono obiektu.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		STyp::Ilosc pobierzIloscObiektu(const Indeks& indeks) const;

		/**
		* \brief Metoda zapisuj�ca.
		*
		* Metoda s�u��ca do zapisu danych do w�z�a xml podanego jako parametr.
		* \param[out] wezel - W�ze� do kt�rego s� zapisywane dane.
		* \return Zwracana jest warto�� true, je�eli zapisano obiekt poprawnie. False, je�eli zapis si� nie powi�d�.
		* \warning Je�eli zwr�cono warto�� false w�ze� przekazany jako parametr nie jest zmodyfokowany.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
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
		* \date 14-07-2014
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		*/
		std::string napis() const override;

		/**
		* \brief Metoda dodaj�ca obiekt gry do planety.
		*
		* Metoda dodaje obiekt gry do planety. Nie tworzy kopii. Sprawdza czy istnieje obiekt o takim samym identyfikatorze.
		* \param[in] obiekt - Sprytny wska�nik na dodawany obiekt.
		* \return true je�eli uda si� doda� obiekt, fasle w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 3
		* \date 07-10-2014
		*/	
		template < class T>
		bool dodajObiekt(typename T::SharedPtr obiekt){
			return false;
		}
		
		template < >
		bool dodajObiekt<Surowce>(Surowce::SharedPtr obiekt){
			return dodajObiekt<Surowce>(listaSurowcow_, obiekt);
		}

		template < >
		bool dodajObiekt<Technologia>(Technologia::SharedPtr obiekt){
			return dodajObiekt<Technologia>(listaTechnologii_, obiekt);
		}

		template < >
		bool dodajObiekt<Obrona>(Obrona::SharedPtr obiekt){
			return dodajObiekt<Obrona>(listaObrona_, obiekt);
		}

		template < >
		bool dodajObiekt<Statek>(Statek::SharedPtr obiekt){
			return dodajObiekt<Statek>(listaStatkow_, obiekt);
		}

		template < >
		bool dodajObiekt<Budynek>(Budynek::SharedPtr obiekt){
			return dodajObiekt<Budynek>(listaBudynkow_, obiekt);
		}

	private:

		/**
		* \brief Metoda obs�uguj�ca b��d wyszukiwania.
		*
		* Metoda w zdefiniowany spos�b reaguje na b��d wyszukiwania.
		* \param[in] identyfikator - Identyfikator wyszukiwanego obiektu.
		* \return Zwracany jest nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 07-10-2014
		*/
		template < class T, class TRAIT>
		typename std::enable_if<std::is_same<TRAIT, NOTHROW>::value, typename T::ConstSharedPtr>::type obsluzBladWyszukiwania(const STyp::Identyfikator& identyfikator) const{
			return nullptr;
		}

		/**
		* \brief Metoda obs�uguj�ca b��d wyszukiwania.
		*
		* Metoda w zdefiniowany spos�b reaguje na b��d wyszukiwania.
		* \param[in] identyfikator - Identyfikator wyszukiwanego obiektu.
		* \return Generowany jest wyj�tek, metoda nie zwraca warto�ci.
		* \author Daniel Wojdak
		* \version 1
		* \date 07-10-2014
		*/
		template < class T, class TRAIT>
		typename std::enable_if<std::is_same<TRAIT, THROW>::value, typename T::ConstSharedPtr>::type obsluzBladWyszukiwania(const STyp::Identyfikator& identyfikator) const{
			throw NieznalezionoObiektu(EXCEPTION_PLACE, identyfikator.napis());
		}

		/**
		* \brief Metoda obs�uguj�ca b��d wyszukiwania.
		*
		* Metoda w zdefiniowany spos�b reaguje na b��d wyszukiwania.
		* \param[in] identyfikator - Identyfikator wyszukiwanego obiektu.
		* \return Zwracany jest nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 07-10-2014
		*/
		template < class T, class TRAIT>
		typename std::enable_if<std::is_same<TRAIT, NOTHROW>::value, typename T::SharedPtr>::type obsluzBladWyszukiwania(const STyp::Identyfikator& identyfikator){
			return nullptr;
		}

		/**
		* \brief Metoda obs�uguj�ca b��d wyszukiwania.
		*
		* Metoda w zdefiniowany spos�b reaguje na b��d wyszukiwania.
		* \param[in] identyfikator - Identyfikator wyszukiwanego obiektu.
		* \return Generowany jest wyj�tek, metoda nie zwraca warto�ci.
		* \author Daniel Wojdak
		* \version 1
		* \date 07-10-2014
		*/
		template < class T, class TRAIT>
		typename std::enable_if<std::is_same<TRAIT, THROW>::value, typename T::SharedPtr>::type obsluzBladWyszukiwania(const STyp::Identyfikator& identyfikator){
			throw NieznalezionoObiektu(EXCEPTION_PLACE, identyfikator.napis());
		}

		/**
		* \brief Metoda dodaj�ca obiekt gry do planety.
		*
		* Metoda dodaje obiekt gry do planety. Nie tworzy kopii. Sprawdza czy istnieje obiekt o takim samym identyfikatorze.
		* \param[in] obiekt - Sprytny wska�nik na dodawany obiekt.
		* \param[in] lista - Specjalizowana lista, do kt�rej ma zosta� dodany obiekt.
		* \return true je�eli uda si� doda� obiekt, fasle w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 3
		* \date 07-10-2014
		*/
		template < class T , class K >
		bool dodajObiekt(K& lista, typename T::SharedPtr obiekt){
			auto iterator = listaObiektow_.find(obiekt->pobierzIdentyfikator());
			if (iterator != listaObiektow_.end()){
				return iterator->second->polacz(*obiekt);
			}
			obiekt->ustawIdentyfikatorPlanety(identyfikator_);
			lista.insert(std::make_pair(obiekt->pobierzIdentyfikator(), obiekt));
			listaObiektow_.insert(std::make_pair(obiekt->pobierzIdentyfikator(), obiekt));
			return true;
		}

		/**
		* \brief Metoda wyszukuje obiekt o podanym identyfikatorze.
		*
		* Metoda wyszukuje z planety obiekt o podanym identyfikatorze.
		* \param[in] identyfikator - Identyfikator obiektu.
		* \param[in] lista - lista obiekt�w, w kt�rej jest wyszukiwany obiekt.
		* \return Referencja do obiektu. Je�eli obiekt nie zostanie znaleziony podejmowane dzia�anie zale�y od typu TRAIT.
		* \author Daniel Wojdak
		* \version 1
		* \date 07-10-2014
		*/
		template < class T, class TRAIT, class K >
		typename T::ConstSharedPtr znajdzObiekt(const K& lista, const STyp::Identyfikator& identyfikator)const{
			auto iterator = lista.find(identyfikator);
			if (iterator == lista.end())
				return obsluzBladWyszukiwania<T, TRAIT>(identyfikator);
			return iterator->second;
		}

		/**
		* \brief Metoda wyszukuje obiekt o podanym identyfikatorze.
		*
		* Metoda wyszukuje z planety obiekt o podanym identyfikatorze.
		* \param[in] identyfikator - Identyfikator obiektu.
		* \param[in] lista - lista obiekt�w, w kt�rej jest wyszukiwany obiekt.
		* \return Referencja do obiektu. Je�eli obiekt nie zostanie znaleziony podejmowane dzia�anie zale�y od typu TRAIT.
		* \author Daniel Wojdak
		* \version 1
		* \date 07-10-2014
		*/
		template < class T, class TRAIT, class K >
		typename T::SharedPtr znajdzObiekt(const K& lista, const STyp::Identyfikator& identyfikator){
			auto iterator = lista.find(identyfikator);
			if (iterator == lista.end())
				return obsluzBladWyszukiwania<T, TRAIT>(identyfikator);
			return iterator->second;
		}

		/**
		* \brief Metoda wyszukuje obiekt o podanym identyfikatorze.
		*
		* Metoda wyszukuje z planety obiekt o podanym identyfikatorze.
		* \param[in] identyfikator - Identyfikator obiektu.
		* \return Referencja do obiektu. Je�eli obiekt nie zostanie znaleziony podejmowane dzia�anie zale�y od typu TRAIT.
		* \author Daniel Wojdak
		* \version 1
		* \date 07-10-2014
		*/
		template < class T, class TRAIT>
		typename std::enable_if<std::is_same<T, Obiekt>::value, typename T::ConstSharedPtr>::type znajdzObiekt(const STyp::Identyfikator& identyfikator)const{
			return znajdzObiekt<T, TRAIT>(listaObiektow_, identyfikator);
		}

		template < class T, class TRAIT>
		typename std::enable_if<std::is_same<T, Statek>::value, typename T::ConstSharedPtr>::type znajdzObiekt(const STyp::Identyfikator& identyfikator)const{
			return znajdzObiekt<T, TRAIT>(listaStatkow_, identyfikator);
		}

		template < class T, class TRAIT>
		typename std::enable_if<std::is_same<T, Obrona>::value, typename T::ConstSharedPtr>::type znajdzObiekt(const STyp::Identyfikator& identyfikator)const{
			return znajdzObiekt<T, TRAIT>(listaObrona_, identyfikator);
		}

		template < class T, class TRAIT>
		typename std::enable_if<std::is_same<T, Surowce>::value, typename T::ConstSharedPtr>::type znajdzObiekt(const STyp::Identyfikator& identyfikator)const{
			return znajdzObiekt<T, TRAIT>(listaSurowcow_, identyfikator);
		}

		template < class T, class TRAIT>
		typename std::enable_if<std::is_same<T, Budynek>::value, typename T::ConstSharedPtr>::type znajdzObiekt(const STyp::Identyfikator& identyfikator)const{
			return znajdzObiekt<T, TRAIT>(listaBudynkow_, identyfikator);
		}

		template < class T, class TRAIT>
		typename std::enable_if<std::is_same<T, Technologia>::value, typename T::ConstSharedPtr>::type znajdzObiekt(const STyp::Identyfikator& identyfikator)const{
			return znajdzObiekt<T, TRAIT>(listaTechnologii_, identyfikator);
		}

		template < class T, class TRAIT>
		typename std::enable_if<std::is_same<T, Flota>::value, typename T::ConstSharedPtr>::type znajdzObiekt(const STyp::Identyfikator& identyfikator)const{
			return znajdzObiekt<T, TRAIT>(listaFlot_, identyfikator);
		}

		/**
		* \brief Metoda wyszukuje obiekt o podanym identyfikatorze.
		*
		* Metoda wyszukuje z planety obiekt o podanym identyfikatorze.
		* \param[in] identyfikator - Identyfikator obiektu.
		* \return Referencja do obiektu. Je�eli obiekt nie zostanie znaleziony podejmowane dzia�anie zale�y od typu TRAIT.
		* \author Daniel Wojdak
		* \version 1
		* \date 07-10-2014
		*/
		template < class T, class TRAIT>
		typename std::enable_if<std::is_same<T, Obiekt>::value, typename T::SharedPtr>::type znajdzObiekt(const STyp::Identyfikator& identyfikator){
			return znajdzObiekt<T, TRAIT>(listaObiektow_, identyfikator);
		}

		template < class T, class TRAIT>
		typename std::enable_if<std::is_same<T, Statek>::value, typename T::SharedPtr>::type znajdzObiekt(const STyp::Identyfikator& identyfikator){
			return znajdzObiekt<T, TRAIT>(listaStatkow_, identyfikator);
		}

		template < class T, class TRAIT>
		typename std::enable_if<std::is_same<T, Obrona>::value, typename T::SharedPtr>::type znajdzObiekt(const STyp::Identyfikator& identyfikator){
			return znajdzObiekt<T, TRAIT>(listaObrona_, identyfikator);
		}

		template < class T, class TRAIT>
		typename std::enable_if<std::is_same<T, Surowce>::value, typename T::SharedPtr>::type znajdzObiekt(const STyp::Identyfikator& identyfikator){
			return znajdzObiekt<T, TRAIT>(listaSurowcow_, identyfikator);
		}

		template < class T, class TRAIT>
		typename std::enable_if<std::is_same<T, Budynek>::value, typename T::SharedPtr>::type znajdzObiekt(const STyp::Identyfikator& identyfikator){
			return znajdzObiekt<T, TRAIT>(listaBudynkow_, identyfikator);
		}

		template < class T, class TRAIT>
		typename std::enable_if<std::is_same<T, Technologia>::value, typename T::SharedPtr>::type znajdzObiekt(const STyp::Identyfikator& identyfikator){
			return znajdzObiekt<T, TRAIT>(listaTechnologii_, identyfikator);
		}

		template < class T, class TRAIT>
		typename std::enable_if<std::is_same<T, Flota>::value, typename T::SharedPtr>::type znajdzObiekt(const STyp::Identyfikator& identyfikator){
			return znajdzObiekt<T, TRAIT>(listaFlot_, identyfikator);
		}

		/**
		* \brief Metoda ustawia w�a�ciciela planety.
		*
		* Metoda zamienia bierz�cego w�a�ciciela na podanego w parametrze.
		* \param[in] uzytkownik - Wska�nik na u�ytkownika.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		void ustawWlasciciela(Uzytkownik* uzytkownik);

		/**
		* \brief Metoda pobiera w�a�ciciela.
		*
		* Metoda pobiera w�a�ciciela planety.
		* \return Wska�nika na w�a�ciciela.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
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
		STyp::Temperatura temperaturaPlanety_; /// Atrybut przechowuj�cy informacje o �redniej temperaturze planety.
		STyp::Powierzchnia calkowitaPowierzchniaPlanety_; /// Atrybut przehcowuj�cy informacje o ca�kowitej powierzchni planety.
		STyp::Powierzchnia powierzchniaZajetaPrzezWode_; /// Atrybut przechowuj�cy informacje o powierzchni planety zaj�tej przez wod�.
		STyp::Powierzchnia powierzchniaLadow_; /// Atrybut przechowuj�cy informacje o powierzchni planety zaj�tej przez l�dy.
		STyp::Powierzchnia powierzchniaUzytkowaLadow_; /// Atrybut przechowuj�cy informacje o powierzchni u�ytkowej planety.
		STyp::Tekst nazwaPlanety_; /// Nazwa planety.

		STyp::Identyfikator identyfikator_; /// Identyfikator planety.
		STyp::Identyfikator idUkladu_; /// Uk�ad s�oneczny w kt�rym znajduje si� planeta.
		STyp::Tekst idUzytkownika_; /// Nazwa u�ytkownika przypisanego do planety.
	};
}
