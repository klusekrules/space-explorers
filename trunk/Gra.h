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
	* \brief Klasa reprezentuj¹ca grê.
	*
	* Klasa przechowuje wszystkie informacje i obiekty do poprawnego dzia³ania gry.
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
		typedef std::unordered_map<STyp::Identyfikator, SurowceInfo::ConstSharedPtr, STyp::IdTypeHash > ListaSurowcowInfoTyp; /// Typ listy obiektów opisowych surowców.
		typedef std::unordered_map<STyp::Identyfikator, StatekInfo::ConstSharedPtr, STyp::IdTypeHash > ListaStatkowInfoTyp; /// Typ listy obiektów opisowych statku.
		typedef std::unordered_map<STyp::Identyfikator, ObronaInfo::ConstSharedPtr, STyp::IdTypeHash > ListaObronyInfoTyp; /// Typ listy obiektów opisowych obrony.
		typedef std::unordered_map<STyp::Identyfikator, TechnologiaInfo::ConstSharedPtr, STyp::IdTypeHash > ListaTechnologiInfoTyp; /// Typ listy obiektów opisowych  technologii.
		typedef std::unordered_map<STyp::Identyfikator, BudynekInfo::ConstSharedPtr, STyp::IdTypeHash > ListaBudynkowInfoTyp; /// Typ listy obiektów opisowych budynku.
		typedef std::unordered_map<STyp::Identyfikator, ObiektInfo::ConstSharedPtr, STyp::IdTypeHash > ListaObiektowInfoTyp; /// Typ listy obiektów opisowych.

		/**
		* \brief Konstruktor.
		*
		* \param[in] logger - instancja loggera.
		* \param[in] zarzadcaLokacji - instancja zarz¹dcy lokacji.
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
		* \brief Metoda wszytuj¹ca dane z pliku.
		*
		* Metoda wczytuje obiekty opisowe.
		* \param[in] root - Wêze³ z którego maj¹ zostaæ wczytane dane.
		* \return Zwraca wartoœæ true, je¿eli uda siê wczytaæ dane, false w przeciwnym wypadku.
		*/
		bool wczytajDane(std::shared_ptr<SPar::ParserElement> root);

		/**
		* \brief Metoda pobiera aktualnie zalogowanego u¿ytkownika.
		*
		* Metoda s³u¿y do pobrania aktualnie zalogowanego u¿ytkownika.
		* \return Referencja do zalogowanego u¿ytkownika.
		* \throw NieznalezionoObiektu
		*/
		Uzytkownik& pobierzUzytkownika() const throw (NieznalezionoObiektu);

		/**
		* \brief Metoda przenosi planetê do zalogowane u¿ytkownika.
		*
		* Metoda przenosi planetê o podanym identyfikatorze do aktualnie zalogowanego u¿ytkownika. Przypisuje jego jako w³aœciciela. Usuwa planetê z listy wolnych planet.
		* \param[in] identyfikator - identyfikator planety.
		* \return true je¿eli uda siê przeniœæ, false w przeciwnym wypadku.
		*/
		bool przeniesPlaneteDoUzytkownika(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Metoda przenosi planetê do zalogowane u¿ytkownika.
		*
		* Metoda przenosi pierwsz¹ woln¹ planetê do aktualnie zalogowanego u¿ytkownika. Przypisuje jego jako w³aœciciela. Usuwa planetê z listy wolnych planet.
		* \return true je¿eli uda siê przeniœæ, false w przeciwnym wypadku.
		*/
		bool przeniesPlaneteDoUzytkownika();

		/**
		* \brief Metoda loguj¹ca u¿ytkownika.
		*
		* Metoda s³u¿y do logowania u¿ytkownika. Zostaj¹ za³adowane do pamiêci planety nale¿¹ce do u¿ytkownika.
		* \param[in] nazwa - Nazwa u¿ytkownika.
		* \param[in] hash - Hash has³a u¿ytkownika.
		* \return Zwraca wartoœæ true, je¿eli uda siê zalogowaæ, false w przeciwnym przypadku.
		*/
		bool logowanie(const std::string& nazwa, const std::string& hash);

		/**
		* \brief Metoda dodaj¹ca nowego u¿ytkownika.
		*
		* Metoda tworzy wêze³ oraz plik z danymi gracza. Sprawdza czy gracz ju¿ istnieje.
		* \param[in] nazwa - Nazwa u¿ytkownika.
		* \param[in] hash - Hash has³a u¿ytkownika.
		* \return Zwraca wartoœæ true, je¿eli uda siê dodaæ u¿ytkownika, false w przeciwnym przypadku.
		*/
		bool nowyGracz(const std::string& nazwa, const std::string& hash);

		/**
		* \brief Metoda usuwaj¹ca u¿ytkownika.
		*
		* Metoda usuwa plik u¿ytkownika, odpinaj¹æ przypisane do niego planety. Usuwa wszystkie obiektu przypisane do planety.
		* \param[in] nazwa - Nazwa u¿ytkownika.
		* \param[in] hash - Hash has³a u¿ytkownika.
		* \return true je¿eli uda siê usun¹æ u¿ytkownika, false w przeciwnym przypadku.
		*/
		bool usunGracza(const std::string& nazwa, const std::string& hash);


		/**
		* \brief Metoda tworz¹ca instancje obiektu nie przypisan¹ do planety.
		*
		* Metoda tworzy obiekt na podstawie wêz³a xml, nie przypisuje go do ¿adnej planety.
		* \param[in] wezel - Wêze³ z którego s¹ odczytywane dane.
		* \return Sprytny wskaŸnik do obiektu. WskaŸnik na nullptr, je¿eli wyst¹pi³ b³¹d.
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
			//TODO: Zamiast zwracania nullptr, generowanie wyj¹tku.
			if (!obiekt || !obiekt->odczytaj(wezel))
				return nullptr;
			return obiekt;
		}

		/**
		* \brief Metoda pobieraj¹ca obiekt opisowy.
		*
		* Metoda pobiera obiekt opisowy.
		* \param[in] identyfikator - identyfikator obiektu.
		* \return Referencja do obiektu opisowego. Je¿eli nie znaleziono obiektu zwraca nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 14-07-2014
		*/
		template <class T>
		typename T::ConstSharedPtr pobierzObiektInfoJesliIstnieje(const STyp::Identyfikator& identyfikator) const{
			return znajdzObiektInfo<T, NOTHROW>(identyfikator);
		}
	
		/**
		* \brief Metoda pobieraj¹ca obiekt opisowy.
		*
		* Metoda pobiera obiekt opisowy.
		* \param[in] identyfikator - identyfikator obiektu.
		* \return Referencja do obiektu opisowego. Je¿eli nie znaleziono obiektu zostaje wyrzucony wyj¹tek.
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
		* \brief Metoda zwracaj¹ca wskaŸnik na planetê.
		*
		* Metoda zwraca wskaŸnik na planetê o wskazanym identyfikatorze.
		* \param[in] identyfikator - Identyfikator planety.
		* \return WskaŸnik na planetê je¿eli planeta zosta³a znaleziona, nullptr w przeciwnym wypadku.
		*/
		std::shared_ptr<Planeta> pobierzPlanete(const STyp::Identyfikator& identyfikator);

		/**
		* \brief Metoda zwraca liczba galaktyk.
		*
		* Metoda zwraca liczba galaktyk zarz¹dzancyh przez zarz¹dcê pamiêci.
		* \return Liczba galaktyk.
		*/
		int pobierzIloscGalaktyk() const;

		/**
		* \brief Metoda generuje now¹ galaktykê.
		*
		* Metoda generuje now¹ galaktykê.
		* \return true je¿eli siê powiedzie, false w przeciwnym wypadku.
		*/
		bool generujNowaGalaktyke();

		/**
		* \brief Metoda zwraca listê wszystkich obiektów opisowych.
		*
		* Metoda zwraca listê wszystkich obiektów opisowych.
		* \return Zwraca listê obiektów.
		*/
		const ListaObiektowInfoTyp& pobierzObiektyInfo(){
			return listaObiektowInfo_;
		}

		/**
		* \brief Metoda Zwraca listê obiektów info spe³niaj¹chych wymagania.
		*
		* Metoda zwraca listê obiektów info, które spe³niaj¹ wymagania rozbudowy na planecie podanej w parametrze oraz obiekt jest tego samego typu przezkazanego w parametrze.
		* \param[in] planeta - Planeta, dla której obliczane s¹ wymagania.
		* \param[in] typObiektu - Typ obiektu jaki ma byæ brany pod uwagê.
		* \param[out] listaIdentyfikatorow - Lista identyfikatorów obiektów zwróconych przez metodê.
		* \return Zwraca listê obiektów spe³niaj¹cych warunki.
		*/
		const ListaObiektowInfoTyp& pobierzDostepneObiektyInfo(const Planeta& planeta, const STyp::Identyfikator& typObiektu, std::vector<STyp::Identyfikator>& listaIdentyfikatorow);

		/**
		* \brief Metoda sprawdza czy u¿ytkownik jest zalogowany.
		*
		* Metoda metoda sprawdzaj¹ca czy zalogowano u¿ytkownika.
		* \return Zwraca wartoœæ true je¿eli u¿ytkownik jest zalogowany, false w przeciwnym przypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 16-06-2014
		*/
		bool czyZalogowano()const{
			return uzytkownik_ != nullptr;
		}
		
		/**
		* Metoda generuj¹ca opis klasy w postaci ci¹gu znaków.
		* \return Napis zwieraj¹cy opis klasy.
		* \author Daniel Wojdak
		* \version 1
		* \date 20-10-2014
		*/
		std::string napis() const override;

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
			throw NieznalezionoObiektu(EXCEPTION_PLACE, Utils::pobierzDebugInfo(), std::to_string(identyfikator()));
		}

		/**
		* \brief Metoda wczytuj¹ca dane obiektow gry.
		*
		* Metoda wczytuje z wêz³a xml dane opisowe obiektów gry. Tworzy obiekty typu T oraz dodaje je do listy wszystkich obiektów i listy przekazanej jako listaInfo.
		* \param[in] wezel - Wêze³ xml zawieraj¹cy dane.
		* \param[in] listaInfo - Specjalizowana lista, do której maj¹ zostaæ wczytane obiekty.
		* \param[in] nazwaWezla - Nazwa wêz³a obiektu gry.
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
		* \brief Metoda pobieraj¹ca obiekt opisowy.
		*
		* Metoda pobiera obiekt opisowy.
		* \param[in] identyfikator - identyfikator obiektu.
		* \return Referencja do obiektu opisowego. Je¿eli nie znaleziono obiektu zostaje wyrzucony wyj¹tek.
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
		* \brief Metoda wyszukuj¹ca obiekt opisowy.
		*
		* Metoda wyszukuje obiekt o podanym identyfikatorze w liœcie obiektów przezkazanej przez parametr.
		* \param[in] listaInfo - Specjalizowana lista, w której wyszukiwany obiekt.
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
				
		SLog::Log& logger_; /// Referencja do obiektu loguj¹cego.
		ZarzadcaLokacji& zarzadcaLokacji_; /// Referencja do aktualnego obiektu zarz¹dcy lokacji.
		std::shared_ptr<Uzytkownik> uzytkownik_; /// Aktualnie zalogowany u¿ytkownik.

		ListaSurowcowInfoTyp listaSurowcowInfo_; /// Lista obiektów opisowych surowców.
		ListaStatkowInfoTyp listaStatkowInfo_; /// Lista obiektów opisowych statku.
		ListaObronyInfoTyp listaObronaInfo_; /// Lista obiektów opisowych obrony.
		ListaTechnologiInfoTyp listaTechnologiInfo_; /// Lista obiektów opisowych technologii.
		ListaBudynkowInfoTyp listaBudynkowInfo_; /// Lista obiektów opisowych budynku.
		ListaObiektowInfoTyp listaObiektowInfo_; /// Lista obiektów opisowych.
		
	};
}
