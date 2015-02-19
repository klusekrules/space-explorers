#pragma once
#include "SurowceInfo.h"
#include "StatekInfo.h"
#include "TechnologiaInfo.h"
#include "BudynekInfo.h"
#include "ObronaInfo.h"
#include "Uzytkownik.h"
#include <unordered_map>
#include "Licznik.h"
#include "GeneratorUkladow.h"
#include "ZarzadcaLokacji.h"
#include "Zmiana\ZmianaFabryka.h"
#include "PowtorzenieIdObiektu.h"

#define KOMUNIKAT_POWTORZENIE_OBIEKTU(a) STyp::Tekst("Obiekt typu: "#a )

namespace SpEx {
	/**
	* \brief Klasa reprezentuj�ca gr�.
	*
	* Klasa przechowuje wszystkie informacje i obiekty do poprawnego dzia�ania gry.
	* \author Daniel Wojdak
	* \version 6
	* \date 25-11-2014
	*/
	class Gra :
		public virtual SLog::LoggerInterface,
		public se::NonCopyable,
		public se::NonMoveable
	{
	public:
		typedef std::unordered_map<STyp::Identyfikator, SurowceInfo::ConstSharedPtr, STyp::IdTypeHash > ListaSurowcowInfoTyp; /// Typ listy obiekt�w opisowych surowc�w.
		typedef std::unordered_map<STyp::Identyfikator, StatekInfo::ConstSharedPtr, STyp::IdTypeHash > ListaStatkowInfoTyp; /// Typ listy obiekt�w opisowych statku.
		typedef std::unordered_map<STyp::Identyfikator, ObronaInfo::ConstSharedPtr, STyp::IdTypeHash > ListaObronyInfoTyp; /// Typ listy obiekt�w opisowych obrony.
		typedef std::unordered_map<STyp::Identyfikator, TechnologiaInfo::ConstSharedPtr, STyp::IdTypeHash > ListaTechnologiInfoTyp; /// Typ listy obiekt�w opisowych  technologii.
		typedef std::unordered_map<STyp::Identyfikator, BudynekInfo::ConstSharedPtr, STyp::IdTypeHash > ListaBudynkowInfoTyp; /// Typ listy obiekt�w opisowych budynku.
		typedef std::unordered_map<STyp::Identyfikator, ObiektInfo::ConstSharedPtr, STyp::IdTypeHash > ListaObiektowInfoTyp; /// Typ listy obiekt�w opisowych.

		/**
		* \brief Konstruktor.
		*
		* \param[in] logger - instancja loggera.
		* \param[in] zarzadcaLokacji - instancja zarz�dcy lokacji.
		* \param[in] ustawieniaAplikacji - ustwaienia aplikacji.
		* \author Daniel Wojdak
		* \version 3
		* \date 25-11-2014
		*/
		explicit Gra(SLog::Log& logger, ZarzadcaLokacji& zarzadcaLokacji, UstawieniaAplikacji& ustawieniaAplikacji);

		/**
		* \brief Destruktor.
		*/
		virtual ~Gra() = default;

		/**
		* \brief Metoda wszytuj�ca dane z pliku.
		*
		* Metoda wczytuje obiekty opisowe.
		* \param[in] root - W�ze� z kt�rego maj� zosta� wczytane dane.
		* \return Zwraca warto�� true, je�eli uda si� wczyta� dane, false w przeciwnym wypadku.
		*/
		bool wczytajDane(std::shared_ptr<SPar::ParserElement> root);

		/**
		* \brief Metoda pobiera aktualnie zalogowanego u�ytkownika.
		*
		* Metoda s�u�y do pobrania aktualnie zalogowanego u�ytkownika.
		* \return Referencja do zalogowanego u�ytkownika.
		* \throw NieznalezionoObiektu
		*/
		Uzytkownik& pobierzUzytkownika() const throw (NieznalezionoObiektu);

		/**
		* \brief Metoda przenosi planet� do zalogowane u�ytkownika.
		*
		* Metoda przenosi planet� o podanym identyfikatorze do aktualnie zalogowanego u�ytkownika. Przypisuje jego jako w�a�ciciela. Usuwa planet� z listy wolnych planet.
		* \param[in] identyfikator - identyfikator planety.
		* \return true je�eli uda si� przeni��, false w przeciwnym wypadku.
		*/
		bool przeniesPlaneteDoUzytkownika(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Metoda przenosi planet� do zalogowane u�ytkownika.
		*
		* Metoda przenosi pierwsz� woln� planet� do aktualnie zalogowanego u�ytkownika. Przypisuje jego jako w�a�ciciela. Usuwa planet� z listy wolnych planet.
		* \return true je�eli uda si� przeni��, false w przeciwnym wypadku.
		*/
		bool przeniesPlaneteDoUzytkownika();

		/**
		* \brief Metoda loguj�ca u�ytkownika.
		*
		* Metoda s�u�y do logowania u�ytkownika. Zostaj� za�adowane do pami�ci planety nale��ce do u�ytkownika.
		* \param[in] nazwa - Nazwa u�ytkownika.
		* \param[in] hash - Hash has�a u�ytkownika.
		* \return Zwraca warto�� true, je�eli uda si� zalogowa�, false w przeciwnym przypadku.
		*/
		bool logowanie(const std::string& nazwa, const std::string& hash);

		/**
		* \brief Metoda dodaj�ca nowego u�ytkownika.
		*
		* Metoda tworzy w�ze� oraz plik z danymi gracza. Sprawdza czy gracz ju� istnieje.
		* \param[in] nazwa - Nazwa u�ytkownika.
		* \param[in] hash - Hash has�a u�ytkownika.
		* \return Zwraca warto�� true, je�eli uda si� doda� u�ytkownika, false w przeciwnym przypadku.
		*/
		bool nowyGracz(const std::string& nazwa, const std::string& hash);

		/**
		* \brief Metoda usuwaj�ca u�ytkownika.
		*
		* Metoda usuwa plik u�ytkownika, odpinaj�� przypisane do niego planety. Usuwa wszystkie obiektu przypisane do planety.
		* \param[in] nazwa - Nazwa u�ytkownika.
		* \param[in] hash - Hash has�a u�ytkownika.
		* \return true je�eli uda si� usun�� u�ytkownika, false w przeciwnym przypadku.
		*/
		bool usunGracza(const std::string& nazwa, const std::string& hash);


		/**
		* \brief Metoda tworz�ca instancje obiektu nie przypisan� do planety.
		*
		* Metoda tworzy obiekt na podstawie w�z�a xml, nie przypisuje go do �adnej planety.
		* \param[in] wezel - W�ze� z kt�rego s� odczytywane dane.
		* \return Sprytny wska�nik do obiektu. Wska�nik na nullptr, je�eli wyst�pi� b��d.
		* \author Daniel Wojdak
		* \version 2
		* \date 06-10-2014
		*/
		template <class T>
		typename T::SharedPtr tworzObiekt(XmlBO::ElementWezla wezel)const throw (NieznalezionoObiektu){
			STyp::Identyfikator identyfikator;
			XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_IDENTYFIKATOR, identyfikator);
			auto& obiektOpisowy = pobierzObiektInfo<typename T::Info>(identyfikator);
			typename T::SharedPtr obiekt = typename T::SharedPtr(obiektOpisowy.tworzEgzemplarz(PodstawoweParametry(PodstawoweParametry::AtrybutPodstawowy(), T::Info::typAtrybutu, STyp::Identyfikator())));
			//TODO: Zamiast zwracania nullptr, generowanie wyj�tku.
			if (!obiekt || !obiekt->odczytaj(wezel))
				return nullptr;
			return obiekt;
		}

		/**
		* \brief Metoda pobieraj�ca obiekt opisowy.
		*
		* Metoda pobiera obiekt opisowy.
		* \param[in] identyfikator - identyfikator obiektu.
		* \return Referencja do obiektu opisowego. Je�eli nie znaleziono obiektu zwraca nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		template <class T>
		typename T::ConstSharedPtr pobierzObiektInfoJesliIstnieje(const STyp::Identyfikator& identyfikator) const{
			return znajdzObiektInfo<T, NOTHROW>(identyfikator);
		}
	
		/**
		* \brief Metoda pobieraj�ca obiekt opisowy.
		*
		* Metoda pobiera obiekt opisowy.
		* \param[in] identyfikator - identyfikator obiektu.
		* \return Referencja do obiektu opisowego. Je�eli nie znaleziono obiektu zostaje wyrzucony wyj�tek.
		* \throw NieznalezionoObiektu
		* \author Daniel Wojdak
		* \version 2
		* \date 19-12-2014
		*/
		template <class T>
		const T& pobierzObiektInfo(const STyp::Identyfikator& identyfikator) const{
			return *(znajdzObiektInfo<T, THROW>(identyfikator));
		}
				
		/**
		* \brief Metoda zwracaj�ca wska�nik na planet�.
		*
		* Metoda zwraca wska�nik na planet� o wskazanym identyfikatorze.
		* \param[in] identyfikator - Identyfikator planety.
		* \return Wska�nik na planet� je�eli planeta zosta�a znaleziona, nullptr w przeciwnym wypadku.
		*/
		std::shared_ptr<Planeta> pobierzPlanete(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Metoda zwraca liczba galaktyk.
		*
		* Metoda zwraca liczba galaktyk zarz�dzancyh przez zarz�dc� pami�ci.
		* \return Liczba galaktyk.
		*/
		int pobierzIloscGalaktyk() const;

		/**
		* \brief Metoda generuje now� galaktyk�.
		*
		* Metoda generuje now� galaktyk�.
		* \return true je�eli si� powiedzie, false w przeciwnym wypadku.
		*/
		bool generujNowaGalaktyke();

		/**
		* \brief Metoda zwraca list� wszystkich obiekt�w opisowych.
		*
		* Metoda zwraca list� wszystkich obiekt�w opisowych.
		* \return Zwraca list� obiekt�w.
		*/
		const ListaObiektowInfoTyp& pobierzObiektyInfo(){
			return listaObiektowInfo_;
		}

		/**
		* \brief Metoda Zwraca list� obiekt�w info spe�niaj�chych wymagania.
		*
		* Metoda zwraca list� obiekt�w info, kt�re spe�niaj� wymagania rozbudowy na planecie podanej w parametrze oraz obiekt jest tego samego typu przezkazanego w parametrze.
		* \param[in] planeta - Planeta, dla kt�rej obliczane s� wymagania.
		* \param[in] typObiektu - Typ obiektu jaki ma by� brany pod uwag�.
		* \param[out] listaIdentyfikatorow - Lista identyfikator�w obiekt�w zwr�conych przez metod�.
		* \return Zwraca list� obiekt�w spe�niaj�cych warunki.
		*/
		const ListaObiektowInfoTyp& pobierzDostepneObiektyInfo(const Planeta& planeta, const STyp::Identyfikator& typObiektu, std::vector<STyp::Identyfikator>& listaIdentyfikatorow);

		/**
		* \brief Metoda sprawdza czy u�ytkownik jest zalogowany.
		*
		* Metoda metoda sprawdzaj�ca czy zalogowano u�ytkownika.
		* \return Zwraca warto�� true je�eli u�ytkownik jest zalogowany, false w przeciwnym przypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 16-06-2014
		*/
		bool czyZalogowano()const{
			return uzytkownik_ != nullptr;
		}
		
		/**
		* Metoda generuj�ca opis klasy w postaci ci�gu znak�w.
		* \return Napis zwieraj�cy opis klasy.
		* \author Daniel Wojdak
		* \version 1
		* \date 20-10-2014
		*/
		std::string napis() const override;

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
			throw NieznalezionoObiektu(EXCEPTION_PLACE, Utils::pobierzDebugInfo(), std::to_string(identyfikator()));
		}

		/**
		* \brief Metoda wczytuj�ca dane obiektow gry.
		*
		* Metoda wczytuje z w�z�a xml dane opisowe obiekt�w gry. Tworzy obiekty typu T oraz dodaje je do listy wszystkich obiekt�w i listy przekazanej jako listaInfo.
		* \param[in] wezel - W�ze� xml zawieraj�cy dane.
		* \param[in] listaInfo - Specjalizowana lista, do kt�rej maj� zosta� wczytane obiekty.
		* \param[in] nazwaWezla - Nazwa w�z�a obiektu gry.
		* \author Daniel Wojdak
		* \version 1
		* \date 03-10-2014
		*/
		template < class T, class K>
		void wczytajObiektyInfo(XmlBO::ElementWezla wezel, K& listaInfo, const char * nazwaWezla){
			XmlBO::ElementWezla element = wezel->pobierzElement(nazwaWezla);
			while (element){
				typename T::SharedPtr obiekt = std::make_shared<T>(element);
#if !(defined(LOG_OFF_ALL) || defined(LOG_OFF_DEBUG))
				logger_.loguj(SLog::Log::Debug, *obiekt);
#endif
				if (listaObiektowInfo_.find(obiekt->pobierzIdentyfikator()) != listaObiektowInfo_.end())
					throw PowtorzenieIdObiektu(EXCEPTION_PLACE, Utils::pobierzDebugInfo(), obiekt->pobierzIdentyfikator(), KOMUNIKAT_POWTORZENIE_OBIEKTU(T));
				listaInfo[obiekt->pobierzIdentyfikator()] = obiekt;
				listaObiektowInfo_[obiekt->pobierzIdentyfikator()] = obiekt;
				element = element->pobierzNastepnyElement(nazwaWezla);
			}
		}

		/**
		* \brief Metoda pobieraj�ca obiekt opisowy.
		*
		* Metoda pobiera obiekt opisowy.
		* \param[in] identyfikator - identyfikator obiektu.
		* \return Referencja do obiektu opisowego. Je�eli nie znaleziono obiektu zostaje wyrzucony wyj�tek.
		* \throw NieznalezionoObiektu
		* \author Daniel Wojdak
		* \version 1
		* \date 03-10-2014
		*/
		template <class T, class TRAIT>
		typename std::enable_if<std::is_same<T, ObiektInfo>::value, typename T::ConstSharedPtr>::type znajdzObiektInfo(const STyp::Identyfikator& identyfikator)const{
			return znajdzObiektInfo<T, TRAIT>(listaObiektowInfo_, identyfikator);
		}

		template <class T, class TRAIT>
		typename std::enable_if<std::is_same<T, ObronaInfo>::value, typename T::ConstSharedPtr>::type znajdzObiektInfo(const STyp::Identyfikator& identyfikator)const{
			return znajdzObiektInfo<T,TRAIT>(listaObronaInfo_, identyfikator);
		}

		template <class T, class TRAIT>
		typename std::enable_if<std::is_same<T, StatekInfo>::value, typename T::ConstSharedPtr>::type znajdzObiektInfo(const STyp::Identyfikator& identyfikator)const{
			return znajdzObiektInfo<T, TRAIT>(listaStatkowInfo_, identyfikator);
		}

		template <class T, class TRAIT>
		typename std::enable_if<std::is_same<T, SurowceInfo>::value, typename T::ConstSharedPtr>::type znajdzObiektInfo(const STyp::Identyfikator& identyfikator)const{
			return znajdzObiektInfo<T, TRAIT>(listaSurowcowInfo_, identyfikator);
		}

		template <class T, class TRAIT>
		typename std::enable_if<std::is_same<T, TechnologiaInfo>::value, typename T::ConstSharedPtr>::type znajdzObiektInfo(const STyp::Identyfikator& identyfikator)const{
			return znajdzObiektInfo<T, TRAIT>(listaTechnologiInfo_, identyfikator);
		}

		template <class T, class TRAIT>
		typename std::enable_if<std::is_same<T, BudynekInfo>::value, typename T::ConstSharedPtr>::type znajdzObiektInfo(const STyp::Identyfikator& identyfikator)const{
			return znajdzObiektInfo<T, TRAIT>(listaBudynkowInfo_, identyfikator);
		}
		
		/**
		* \brief Metoda wyszukuj�ca obiekt opisowy.
		*
		* Metoda wyszukuje obiekt o podanym identyfikatorze w li�cie obiekt�w przezkazanej przez parametr.
		* \param[in] listaInfo - Specjalizowana lista, w kt�rej wyszukiwany obiekt.
		* \param[in] identyfikator - Identyfikator obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 03-10-2014
		*/
		template < class T, class TRAIT, class K > 
		typename T::ConstSharedPtr znajdzObiektInfo(const K& listaInfo, const STyp::Identyfikator& identyfikator)const{
			auto iterator = listaInfo.find(identyfikator);
			if (iterator == listaInfo.end())
				return obsluzBladWyszukiwania<T, TRAIT>(identyfikator);
			return iterator->second;
		}
				
		SLog::Log& logger_; /// Referencja do obiektu loguj�cego.
		ZarzadcaLokacji& zarzadcaLokacji_; /// Referencja do aktualnego obiektu zarz�dcy lokacji.
		std::shared_ptr<Uzytkownik> uzytkownik_; /// Aktualnie zalogowany u�ytkownik.

		ListaSurowcowInfoTyp listaSurowcowInfo_; /// Lista obiekt�w opisowych surowc�w.
		ListaStatkowInfoTyp listaStatkowInfo_; /// Lista obiekt�w opisowych statku.
		ListaObronyInfoTyp listaObronaInfo_; /// Lista obiekt�w opisowych obrony.
		ListaTechnologiInfoTyp listaTechnologiInfo_; /// Lista obiekt�w opisowych technologii.
		ListaBudynkowInfoTyp listaBudynkowInfo_; /// Lista obiekt�w opisowych budynku.
		ListaObiektowInfoTyp listaObiektowInfo_; /// Lista obiekt�w opisowych.
		
	};
}
