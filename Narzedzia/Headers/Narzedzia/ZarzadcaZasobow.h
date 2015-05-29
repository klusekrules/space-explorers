#pragma once
#include "GeneratorIdentyfikatorow.h"
#include "Zasob.h"
#include "NonCopyable.h"
#include <functional>
#include "Parser\XmlBO.h"
#include "Logger\LoggerInterface.h"
#include "UstawieniaAplikacji.h"
#include "CallbackSystemInterfejs.h"
namespace SpEx {
	
	namespace StrukturyZarzadcyZasobow {
		enum WyzwalaczCallback{
			PoRejestracji,
			PoUtworzeniu,
			PobranoPrzechowywany
		};

		typedef CallbackSystemInterfejs < WyzwalaczCallback, const std::string&, Zasob::SharedPtr > CallbackSystem;
		typedef CallbackSystem::Callback CallbackSystemFunction;
	}

	/**
	* \brief Klasa zarz¹dzaj¹ca zasobami.
	*
	* Klasa zarz¹dzaj¹ca zasobami, przechowuje wskaŸniki na zasoby.
	* \author Daniel Wojdak
	* \version 3
	* \date 25-11-2014
	*/
	class NARZEDZIA_API ZarzadcaZasobow :
		public StrukturyZarzadcyZasobow::CallbackSystem,
		public virtual SLog::LoggerInterface,
		se::NonCopyable
	{
	public:
		typedef std::string Parametr; /// Typ parametru przekazywanego do zasobu.
		typedef std::pair < Parametr, std::string > WpisLokalizacjiZasobu; /// Typ wi¹¿¹cy nazwê symboliczn¹ z lokalizacj¹ zasobu.
		typedef std::vector < WpisLokalizacjiZasobu > TablicaLokalizacjiZasobu; /// Tablica powi¹zañ nazw symbolicznych z lokalizacj¹ zasobu.
		typedef STyp::Identyfikator Identyfikator; /// Identyfikator zasobu.
		
		
		/**
		* \brief Klasa pomocnicza przechowywanego zasobu.
		*
		* Klasa pomocnicza, s³u¿¹ca do zarz¹dzania przechowywanymi zasobami.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-11-2014
		*/
		struct WpisZasobu{
			Zasob::WeakPtr weakptr_; /// S³aby wskaŸnik do zasobu.
			Zasob::SharedPtr sharedptr_; /// Silny wskaŸnik do zasobu.
			bool cached_; /// Informacja czy zasób jest przechowywany.
			Parametr parametr_; /// Parametr inicjalizuj¹cy zasób.
		};
		
		typedef std::function< Zasob::SharedPtr(const Parametr&, bool) > Inicjalizator; /// Typ metody tworz¹cej zasób.
		typedef std::unordered_map < Identyfikator, WpisZasobu, STyp::IdTypeHash> MapaZasobow; /// Typ kontenera przechowuj¹cego zasoby.
		typedef std::unordered_map < std::string, Inicjalizator> MapaInicjalizatorow; /// Typ kontenera przechowuj¹cego inicjalizatory.
		

		/**
		* \brief Domyœlny konstruktor.
		*
		* Domyœlny konstruktor.
		*/
		ZarzadcaZasobow() = default;
		
		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~ZarzadcaZasobow() = default;
		
		/**
		* \brief Metoda pobieraj¹ca klucz zasobu.
		*
		* Metoda na podstawie klucza znakowego zwraca klucz liczbowy.
		* \param[in] identyfikator - Napis identyfikuj¹cy zasób.
		* \return Identyfikator liczbowy.
		* \author Daniel Wojdak
		* \version 1
		* \date 02-09-2014
		*/
		Identyfikator pobierzKlucz(const Parametr& identyfikator);

		/**
		* \brief Metoda pobierajaca zasób.
		*
		* Metoda pobiera lub tworzy zasób.
		* \param[in] parametr - Adres pliku na bazie którgo ma zostaæ zainicjalizowany zasób.
		* \param[in] cache - Informacja czy zasób ma byæ lokalnie przechowywany.
		* \param[out] id - Identyfikator utworzonego zasobu.
		* \return WskaŸnik na zasób lub nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		template <class T_>
		inline std::shared_ptr<T_> pobierzZasob(const Parametr& parametr, bool cache = false, Identyfikator& id = Identyfikator()){
			return std::dynamic_pointer_cast<T_>(pobierzZasob(pobierzInicjalizator(typename T_::NazwaTypu_), parametr, parametr, cache, id));
		}

		/**
		* \brief Metoda pobierajaca zasób.
		*
		* Metoda pobiera lub tworzy zasób.
		* \param[in] nazwa - W³asna nazwa identyfikuj¹ca zasób generowana w trakcie dzia³ania programu.
		* \param[in] identyfikator - Identyfikator zasobu.
		* \param[in] parametr - Adres pliku na bazie którgo ma zostaæ zainicjalizowany zasób.
		* \param[in] cache - Informacja czy zasób ma byæ lokalnie przechowywany.
		* \param[out] id - Identyfikator utworzonego zasobu.
		* \return WskaŸnik na zasób lub nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-11-2014
		*/
		template <class T_>
		inline std::shared_ptr<T_> pobierzZasob(const std::string& nazwa, const Parametr& parametr, bool cache = false, Identyfikator& id = Identyfikator()){
			return std::dynamic_pointer_cast<T_>(pobierzZasob(pobierzInicjalizator(typename T_::NazwaTypu_), nazwa, parametr, cache, id));
		}

		/**
		* \brief Metoda pobierajaca zasób.
		*
		* Metoda pobiera lub tworzy zasób.
		* \param[in] parametr - Adres pliku na bazie którgo ma zostaæ zainicjalizowany zasób.
		* \return WskaŸnik na zasób lub nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		template <class T_>
		inline std::shared_ptr<T_> pobierzUnikalnyZasob(const Parametr& parametr){
			return std::dynamic_pointer_cast<T_>(pobierzUnikalnyZasob(pobierzInicjalizator(typename T_::NazwaTypu_), parametr));
		}

		/**
		* \brief Metoda pobiera informacje czy zasób jest przechowywany przez zarz¹dcê.
		*
		* Metoda pobiera informacje czy zasób jest przechowywany lokalnie przez zarz¹dcê zasobów.
		* \param[in] identyfikator - Identyfikator zasobu.
		* \return Zwracana jest wartoœc true, je¿eli zasób jest przechowywany. Zwracana jest wartoœæ false, w przeciwnym przypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		bool przechowywanyZasob(const Identyfikator& identyfikator) const;

		/**
		* \brief Metoda rejestruj¹ca inicjalizator.
		*
		* Metoda rejestruje inicjalizator w zarz¹dcy zasobów.
		* \return Zwracana jest wartoœc true, je¿eli uda siê zarejestrowaæ. Zwracana jest wartoœæ false, w przypadku b³êdu.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		template <class T_>
		bool rejestruj(){
			wywolaj(StrukturyZarzadcyZasobow::PoRejestracji, typename T_::NazwaTypu_, nullptr);
			return dodajInicjalizator(typename T_::NazwaTypu_, std::bind(&ZarzadcaZasobow::tworz<T_>,this,std::placeholders::_1,std::placeholders::_2));
		}

		template <class T_>
		Zasob::SharedPtr tworz(const ZarzadcaZasobow::Parametr& parametr, bool cache){
			Zasob::SharedPtr ptr = std::make_shared<T_>(parametr);
			wywolaj(StrukturyZarzadcyZasobow::PoUtworzeniu, typename T_::NazwaTypu_, ptr);
			return ptr;
		}

		/**
		* \brief Metoda zwalaniaj¹ca przechowywany zasób.
		*
		* Metoda zwalnia zasób przechowywany lokalnie w zarz¹dcy.
		* \param[in] identyfikator - Identyfikator zasobu.
		* \return Zwracana jest wartoœc true, je¿eli jest uda³o siê zwolniæ zasób. Zwracana jest wartoœæ false, w przeciwnym przypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		bool zwolnijZasobPrzechowywany(const Identyfikator& identyfikator);

		/**
		* \brief Metoda inicjuj¹ca dane zarz¹dcy.
		*
		* Metoda pobiera dane i inicjuje obiekt zarz¹dcy na podstawie danych przekazanych przez parametry.
		* \param[in] ustawienia - Obiekt zawierajacy ustawienia apliakcji.
		* \param[in] stos - Funkcja tworz¹ca œlad stosu.
		* \return Zwracana jest wartoœæ true je¿eli uda siê poprawnie zainicjowaæ obiekt.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-11-2014
		*/
		bool inicjalizuj(const UstawieniaAplikacji& ustawienia);

		void rejestrujTypyWbudowane();

		/**
		* \brief Metoda pobieraj¹ca adres obrazka.
		*
		* Metoda pobiera adres obrazka o padanym identyfikatorze.
		* \param[in] identyfikator - Identyfikator obrazka.
		* \return Adres obrazka.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-11-2014
		*/
		const std::string& pobierzAdresObrazka( const STyp::Identyfikator& identyfikator) const;

		/**
		* \brief Metoda pobieraj¹ca identyfikator obrazka.
		*
		* Metoda pobiera identyfikator obrazka na podstawie nazwy obrazka.
		* \param[in] nazwaObrazka - Nazwa obrazka.
		* \return Identyfikator obrazka.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-11-2014
		*/
		STyp::Identyfikator pobierzIdentyfikator(const Parametr& nazwaObrazka) const;

		/**
		* Funkcja s³u¿¹ca jako podstawa do tworzenia napisów z opisem klasy.
		* \return Napis zawieraj¹cy opis klasy.
		* \author Daniel Wojdak
		* \version 1
		* \date 13-11-2014
		*/
		std::string napis() const override;

		/**
		* Funkcja resetuj¹ca stan obiektu.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-11-2014
		*/
		void resetuj();

	private:
		GeneratorIdentyfikatorow generator_; /// Generator identyfikatorów.
		TablicaLokalizacjiZasobu lokalizacjeZasobow_; /// Tablica zawieraj¹ca powi¹zania nazw symbolicznych z lokalizacj¹ zasobu na dysku.
		
		/**
		* \brief Metoda mapuje parametr na identyfikator.
		*
		* Metoda mapuje parametr tekstowy na identyfikator liczbowy.
		* \param[in] parametr - Adres pliku na bazie którgo ma zostaæ zainicjalizowany zasób.
		* \param[out] identyfikator - Identyfikator zasobu.
		* \return Zwracana jest wartoœc true, je¿eli pierwszy raz odwo³ano siê do tego identyfikatora. Zwracana jest wartoœæ false, w przeciwnym przypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		bool mapujIdentyfikator(const Parametr& parametr, Identyfikator& identyfikator);

		Inicjalizator pobierzInicjalizator(const std::string&);

		bool dodajInicjalizator(const std::string&, Inicjalizator);

		/**
		* \brief Metoda pobierajaca zasób.
		*
		* Metoda pobiera lub tworzy zasób.
		* \param[in] parametr - Adres pliku na bazie którgo ma zostaæ zainicjalizowany zasób.
		* \return WskaŸnik na zasób lub nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		Zasob::SharedPtr pobierzUnikalnyZasob(Inicjalizator inicjalizator, const Parametr& parametr);

		/**
		* \brief Metoda pobierajaca zasób.
		*
		* Metoda pobiera lub tworzy zasób.
		* \param[in] nazwa - W³asna nazwa identyfikuj¹ca zasób generowana w trakcie dzia³ania programu.
		* \param[in] identyfikator - Identyfikator zasobu.
		* \param[in] parametr - Adres pliku na bazie którgo ma zostaæ zainicjalizowany zasób.
		* \param[in] cache - Informacja czy zasób ma byæ lokalnie przechowywany.
		* \param[out] id - Identyfikator utworzonego zasobu.
		* \return WskaŸnik na zasób lub nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 25-11-2014
		*/
		Zasob::SharedPtr pobierzZasob(Inicjalizator inicjalizator, const std::string& nazwa, const Parametr& parametr, bool cache = false, Identyfikator& id = Identyfikator());

		/**
		* \brief Metoda pobierajaca zasób.
		*
		* Metoda pobiera lub tworzy zasób.
		* \param[in] identyfikator - Identyfikator zasobu.
		* \param[in] parametr - Adres pliku na bazie którgo ma zostaæ zainicjalizowany zasób.
		* \param[in] cache - Informacja czy zasób ma byæ lokalnie przechowywany.
		* \param[out] id - Identyfikator utworzonego zasobu.
		* \return WskaŸnik na zasób lub nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		Zasob::SharedPtr pobierzZasob(Inicjalizator inicjalizator, const Identyfikator& identyfikator, const Parametr& parametr, bool cache = false, Identyfikator& id = Identyfikator());

		/**
		* \brief Metoda wczytuj¹ca zasób.
		*
		* Metoda wczytuje zasób do pamiêci.
		* \param[in] identyfikator - Identyfikator zasobu.
		* \param[in] parametr - Adres pliku na bazie którgo ma zostaæ zainicjalizowany zasób.
		* \param[in] cache - Informacja czy zasób ma byæ lokalnie przechowywany.
		* \param[out] id - Identyfikator utworzonego zasobu.
		* \return WskaŸnik na zasób lub nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		Zasob::SharedPtr wczytajZasob(Inicjalizator inicjalizator, const Identyfikator& identyfikator, const Parametr& parametr, bool cache = false, Identyfikator& id = Identyfikator());

		MapaZasobow zasobyPrzechowywane_; /// Obiekt przechowuj¹cy zasoby.
		MapaInicjalizatorow inicjalizatory_; /// Obiekt przechowuj¹cy inicjalizatory.
		const std::string pustyNapis_ = std::string(); /// Pusty napis. U¿ywany przy nie znalezieniu adresu obrazka.
	};
};
