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
	* \brief Klasa reprezentuj¹ca planetê.
	*
	* Klasa reprezentuj¹ca planetê.
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
		* \param[in] identyfikatorUkladu - Numer identyfikuj¹cy uk³ad s³oneczny
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		Planeta(const STyp::Identyfikator& identyfikator, const STyp::Identyfikator& identyfikatorUkladu);

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~Planeta(void) = default;
		
		/**
		* \brief Metoda pobieraj¹ca identyfikator.
		*
		* Metoda pobiera identyfikator obiektu.
		* \return Identyfikator obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		const STyp::Identyfikator& pobierzIdentyfikator()const;

		/**
		* \brief Metoda pobiera iloœæ ró¿nych typów obiektów dostêpnych na planecie.
		*
		* \return Iloœæ typów obiektów na planecie.
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
		* \return WskaŸnik obiektu lub nullptr.
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
		* \return Referencja do obiektu. Je¿eli obiekt nie zostanie znaleziony jest wyrzucany wyj¹tek.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		template <class T>
		const T& pobierzObiekt(const Indeks& identyfikator) const{
			return *(znajdzObiekt<T, THROW>(identyfikator));
		}
		
		/**
		* \brief Metoda pobiera listê surowców.
		*
		* Metoda pobiera z planety listê surowców.
		* \return Referencja do listy surowców.
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
		* \return true je¿eli uda siê wybudowaæ obiekt, false w przeciwnym wypadku.
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
		* \param[in] element - Wêze³ opisuj¹cy tworzony obiek.
		* \return true je¿eli uda siê wybudowaæ obiekt, false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		bool wybuduj(const Indeks& identyfikator, const XmlBO::ElementWezla element);
		
		/**
		* \brief Metoda tworzy flotê na planecie.
		*
		* Metoda tworzy pusty obiekt floty na planecie i zwraca identyfikator.
		* \return Identyfikator nowo stworzonej floty.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		Indeks dodajFlote();

		/**
		* \brief Metoda usuwaj¹ca flotê z planety.
		*
		* Metoda usuwa flotê z listy flot na planecie. Nie roz³adowuje jej ani nie przenosi statków na planete.
		* \param[in] identyfikator - Identyfikator floty do usuniêcia.
		* \return true je¿eli uda³o siê usun¹æ, false w przecwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		bool usunFlote(const Indeks& identyfikator);

		/**
		* \brief Metoda przenoœci obiekt do floty.
		*
		* Metoda przenosi obiekt z planety do floty.
		* \param[in] flota - Identyfikator floty do której ma zostaæ przeniesiony obiekt.
		* \param[in] obiekt - Identyfikator obiektu, który ma byc przenisiony do floty.
		* \param[in] ilosc - Iloœæ obiektów do przeniesienia.
		* \return true je¿eli uda siê przenieœæ obiekt, false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		bool przeniesDoFloty(const Indeks& flota, const Indeks& obiekt, const STyp::Ilosc& ilosc);

		/**
		* \brief Metoda przenoœci obiekt do ³adowni floty.
		*
		* Metoda przenosi obiekt z planety do ³adowni floty.
		* \param[in] flota - Identyfikator floty do ³adowni której ma zostaæ przeniesiony obiekt.
		* \param[in] obiekt - Identyfikator obiektu, który ma byc przenisiony do ³adowni floty.
		* \param[in] ilosc - Iloœæ obiektów do przeniesienia.
		* \return true je¿eli uda siê przenieœæ obiekt, false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		bool zaladujSurowceNaFlote(const Indeks& flota, const Indeks& obiekt, const STyp::Ilosc& ilosc);

		/**
		* \brief Metoda przenoœci obiekt do hangaru floty.
		*
		* Metoda przenosi obiekt z planety do hangaru floty.
		* \param[in] flota - Identyfikator floty do hangaru której ma zostaæ przeniesiony obiekt.
		* \param[in] obiekt - Identyfikator obiektu, który ma byc przenisiony do hangaru floty.
		* \param[in] ilosc - Iloœæ obiektów do przeniesienia.
		* \return true je¿eli uda siê przenieœæ obiekt, false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		bool zaladujStatekNaFlote(const Indeks& flota, const Indeks& obiekt, const STyp::Ilosc& ilosc);

		/**
		* \brief Metoda rozladowujaca statek.
		*
		* Metoda przenosi obiekty z ³adowni na planetê.
		* \param[in] statek - Statek do roz³adowania
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		* \todo Metoda oznaczona do przeniesienia do klasy Statek.
		*/
		void rozladujStatek(Statek::SharedPtr statek);

		/**
		* \brief Metoda sprawdzaj¹ca czy planeta ma w³asciciela.
		*
		* \return true je¿eli obiekt posiada w³aœciciela, false w przeciwnym przypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		bool czyMaWlasciciela()const;

		/**
		* \brief Metoda pobieraj¹ca nazwê planety.
		*
		* Metoda pobiera nazwê planety
		* \return Nazwa planety.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		STyp::Tekst pobierzNazwePlanety() const;

		/**
		* \brief Metoda ustawiaj¹ca nazwê planety.
		*
		* Metoda ustawia nazwê planety
		* \param[in] nazwa - Nowa nazwa planety.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		void ustawNazwePlanety(const STyp::Tekst& nazwa);

		/**
		* \brief Metoda ustawia temperaturê.
		*
		* Metoda ustawiaj¹ca œredni¹ temperaturê na planecie.
		* \param[in] temperatura - wartoœæ temperatury w kelwinach, jaka ma byæ ustawiona w obiekcie.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		void ustawTemperature(const STyp::Temperatura& temperatura);

		/**
		* \brief Metoda ustawia œrednicê.
		*
		* Metoda ustawiaj¹ca œrednicê planety.
		* \param[in] srednica - wartoœæ srednicy w mln km, jaka ma byæ ustawiona w obiekcie.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		void ustawSrednice(const STyp::Dystans& srednica);

		/**
		* \brief Metoda ustawia odleg³oœæ od œrodka uk³adu s³onecznego.
		*
		* Metoda ustawiaj¹ca odleg³oœæ planety od œrodka uk³adu s³onecznego.
		* \param[in] odleglosc - wartoœæ odleglosci w mln km, jaka ma byæ ustawiona w obiekcie.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		void ustawOdlegloscOdSrodkaUkladu(const STyp::Dystans& odleglosc);

		/**
		* \brief Metoda przeliczaj¹ca powierzchnie.
		*
		* Metoda przelicza powierzchniê na planecie wed³ug podanych proporcji.
		* \param[in] procentWody - procenty powierzchni bêd¹cej wod¹.
		* \param[in] procentUzytkowa - procent powierzchni u¿ytkowej.
		* \return true je¿eli argumety s¹ w poprawnym zakresie false w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		bool wyliczPowierzchnie(const STyp::Fluktuacja& procentWody, const STyp::Fluktuacja& procentUzytkowa);

		/**
		* \brief Metoda zwracaj¹ca identyfikator uk³adu rodzica.
		*
		* Metoda zwraca identyfikator uk³adu s³onecznego w którym znajduje sie planeta.
		* \return Identyfikator uk³adu.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		const STyp::Identyfikator& pobierzIdUkladu() const;

		/**
		* \brief Metoda czyœci zawartoœæ planety.
		*
		* Metoda czyœci zawartoœæ planety. Usuwa tak¿e powi¹zanie z u¿ytkownikiem je¿eli takowe istnieje oraz zalogowany jest u¿ytkownik który jest przypisany do planety.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		void wyczyscZawartoscPlanety();

		/**
		* \brief Metoda od³¹czaj¹ca planetê.
		*
		* Metoda od³¹cza planetê od w³aœciciela.
		* \return Wartoœæ true, je¿eli od³¹czono w³aœciciela lub nie ma w³aœciciela, wartoœæ false, je¿eli nie uda³o siê od³¹czyæ w³aœciciela.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		bool odepnijPlanete();

		/**
		* \brief Metoda zwracaj¹ca poziom obiektu.
		*
		* Metoda zwraca nawy¿szy poziom obiektu o podanym identyfikatorze.
		* \param[in] identyfikator - Numer identyfikuj¹cy obiekt.
		* \return Poziom obiektu lub 0 je¿eli nie znaleziono obiektu.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		STyp::Poziom pobierzPoziomObiektu(const Indeks& identyfikator) const;

		/**
		* \brief Metoda zwracaj¹ca iloœæ obiektu.
		*
		* Metoda zwraca iloœæobiektu o podanym indeksie.
		* \param[in] indeks - Indeks obiekt.
		* \return Iloœæ obiektu lub 0 je¿eli nie znaleziono obiektu.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		STyp::Ilosc pobierzIloscObiektu(const Indeks& indeks) const;

		/**
		* \brief Metoda zapisuj¹ca.
		*
		* Metoda s³u¿¹ca do zapisu danych do wêz³a xml podanego jako parametr.
		* \param[out] wezel - Wêze³ do którego s¹ zapisywane dane.
		* \return Zwracana jest wartoœæ true, je¿eli zapisano obiekt poprawnie. False, je¿eli zapis siê nie powiód³.
		* \warning Je¿eli zwrócono wartoœæ false wêze³ przekazany jako parametr nie jest zmodyfokowany.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
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
		* \date 14-07-2014
		*/
		bool odczytaj(XmlBO::ElementWezla wezel) override;

		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		*/
		std::string napis() const override;

		/**
		* \brief Metoda dodaj¹ca obiekt gry do planety.
		*
		* Metoda dodaje obiekt gry do planety. Nie tworzy kopii. Sprawdza czy istnieje obiekt o takim samym identyfikatorze.
		* \param[in] obiekt - Sprytny wskaŸnik na dodawany obiekt.
		* \return true je¿eli uda siê dodaæ obiekt, fasle w przeciwnym wypadku.
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
		* \brief Metoda obs³uguj¹ca b³¹d wyszukiwania.
		*
		* Metoda w zdefiniowany sposób reaguje na b³¹d wyszukiwania.
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
		* \brief Metoda obs³uguj¹ca b³¹d wyszukiwania.
		*
		* Metoda w zdefiniowany sposób reaguje na b³¹d wyszukiwania.
		* \param[in] identyfikator - Identyfikator wyszukiwanego obiektu.
		* \return Generowany jest wyj¹tek, metoda nie zwraca wartoœci.
		* \author Daniel Wojdak
		* \version 1
		* \date 07-10-2014
		*/
		template < class T, class TRAIT>
		typename std::enable_if<std::is_same<TRAIT, THROW>::value, typename T::ConstSharedPtr>::type obsluzBladWyszukiwania(const STyp::Identyfikator& identyfikator) const{
			throw NieznalezionoObiektu(EXCEPTION_PLACE, identyfikator.napis());
		}

		/**
		* \brief Metoda obs³uguj¹ca b³¹d wyszukiwania.
		*
		* Metoda w zdefiniowany sposób reaguje na b³¹d wyszukiwania.
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
		* \brief Metoda obs³uguj¹ca b³¹d wyszukiwania.
		*
		* Metoda w zdefiniowany sposób reaguje na b³¹d wyszukiwania.
		* \param[in] identyfikator - Identyfikator wyszukiwanego obiektu.
		* \return Generowany jest wyj¹tek, metoda nie zwraca wartoœci.
		* \author Daniel Wojdak
		* \version 1
		* \date 07-10-2014
		*/
		template < class T, class TRAIT>
		typename std::enable_if<std::is_same<TRAIT, THROW>::value, typename T::SharedPtr>::type obsluzBladWyszukiwania(const STyp::Identyfikator& identyfikator){
			throw NieznalezionoObiektu(EXCEPTION_PLACE, identyfikator.napis());
		}

		/**
		* \brief Metoda dodaj¹ca obiekt gry do planety.
		*
		* Metoda dodaje obiekt gry do planety. Nie tworzy kopii. Sprawdza czy istnieje obiekt o takim samym identyfikatorze.
		* \param[in] obiekt - Sprytny wskaŸnik na dodawany obiekt.
		* \param[in] lista - Specjalizowana lista, do której ma zostaæ dodany obiekt.
		* \return true je¿eli uda siê dodaæ obiekt, fasle w przeciwnym wypadku.
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
		* \param[in] lista - lista obiektów, w której jest wyszukiwany obiekt.
		* \return Referencja do obiektu. Je¿eli obiekt nie zostanie znaleziony podejmowane dzia³anie zale¿y od typu TRAIT.
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
		* \param[in] lista - lista obiektów, w której jest wyszukiwany obiekt.
		* \return Referencja do obiektu. Je¿eli obiekt nie zostanie znaleziony podejmowane dzia³anie zale¿y od typu TRAIT.
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
		* \return Referencja do obiektu. Je¿eli obiekt nie zostanie znaleziony podejmowane dzia³anie zale¿y od typu TRAIT.
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
		* \return Referencja do obiektu. Je¿eli obiekt nie zostanie znaleziony podejmowane dzia³anie zale¿y od typu TRAIT.
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
		* \brief Metoda ustawia w³aœciciela planety.
		*
		* Metoda zamienia bierz¹cego w³aœciciela na podanego w parametrze.
		* \param[in] uzytkownik - WskaŸnik na u¿ytkownika.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		void ustawWlasciciela(Uzytkownik* uzytkownik);

		/**
		* \brief Metoda pobiera w³aœciciela.
		*
		* Metoda pobiera w³aœciciela planety.
		* \return WskaŸnika na w³aœciciela.
		* \author Daniel Wojdak
		* \version 2
		* \date 14-07-2014
		*/
		Uzytkownik* pobierzWlasciciela() const;

		Licznik licznikIdentyfikatorowFloty_; /// Licznik identyfikatorów flot.
		Uzytkownik* wlasciciel_; /// W³aœciciel planety.

		ListaSurowcow listaSurowcow_; /// Lista surowców planety.
		ListaStatkow listaStatkow_; /// Lista statków planety
		ListaObrona listaObrona_; /// Lista statków planety
		ListaTechnologii listaTechnologii_; /// Lista tehcnologii planety.
		ListaBudynkow listaBudynkow_; /// Lista budynków planety.
		ListaObiektow listaObiektow_; /// Lista wszystkich obiektów planety.
		ListaFlot listaFlot_; /// Lista flot planety.

		/* Lista parametrów planety */
		STyp::Dystans srednicaPlanety_; /// Atrybut przechowuje informacje o œrednicy planety.
		STyp::Dystans odlegloscOdSlonca_; /// Atrybut przechowuje informacje o odleg³oœci planety od centrum uk³adu s³onecznego.
		STyp::Temperatura temperaturaPlanety_; /// Atrybut przechowuj¹cy informacje o œredniej temperaturze planety.
		STyp::Powierzchnia calkowitaPowierzchniaPlanety_; /// Atrybut przehcowuj¹cy informacje o ca³kowitej powierzchni planety.
		STyp::Powierzchnia powierzchniaZajetaPrzezWode_; /// Atrybut przechowuj¹cy informacje o powierzchni planety zajêtej przez wodê.
		STyp::Powierzchnia powierzchniaLadow_; /// Atrybut przechowuj¹cy informacje o powierzchni planety zajêtej przez l¹dy.
		STyp::Powierzchnia powierzchniaUzytkowaLadow_; /// Atrybut przechowuj¹cy informacje o powierzchni u¿ytkowej planety.
		STyp::Tekst nazwaPlanety_; /// Nazwa planety.

		STyp::Identyfikator identyfikator_; /// Identyfikator planety.
		STyp::Identyfikator idUkladu_; /// Uk³ad s³oneczny w którym znajduje siê planeta.
		STyp::Tekst idUzytkownika_; /// Nazwa u¿ytkownika przypisanego do planety.
	};
}
