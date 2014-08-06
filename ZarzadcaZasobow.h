#pragma once
#include "GeneratorIdentyfikatorow.h"
#include "Zasob.h"
#include "NonCopyable.h"
#include <functional>

namespace SpEx {
	/**
	* \brief Klasa zarz¹dzaj¹ca zasobami.
	*
	* Klasa zarz¹dzaj¹ca zasobami, przechowuje wskaŸniki na zasoby.
	* \author Daniel Wojdak
	* \version 1
	* \date 06-08-2014
	*/
	class ZarzadcaZasobow
		: se::NonCopyable
	{
	public:
		typedef std::string Parametr; /// Typ parametru przekazywanego do zasobu.
		typedef STyp::Identyfikator Identyfikator; /// Identyfikator zasobu.
		typedef std::pair< std::pair< Zasob::WeakPtr, Zasob::SharedPtr >, bool > WpisZasobu; /// Wpis zasobu przechowanego w zarz¹dcy.
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
		* \brief Metoda pobierajaca zasób.
		*
		* Metoda pobiera lub tworzy zasób.
		* \param[in] parametr - Adres pliku na bazie którgo ma zostaæ zainicjalizowany zasób.
		* \param[in] cache - Informacja czy zasób ma byæ lokalnie przechowywany.
		* \return WskaŸnik na zasób lub nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		Zasob::SharedPtr pobierzZasob(const Parametr& parametr, bool cache = false);
		
		/**
		* \brief Metoda pobierajaca zasób.
		*
		* Metoda pobiera lub tworzy zasób.
		* \param[in] parametr - Adres pliku na bazie którgo ma zostaæ zainicjalizowany zasób.
		* \param[in] cache - Informacja czy zasób ma byæ lokalnie przechowywany.
		* \return WskaŸnik na zasób lub nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		template <class T_>
		inline std::shared_ptr<T_> pobierzZasob(const Parametr& parametr, bool cache = false){
			return std::dynamic_pointer_cast<T_>(pobierzZasob(parametr, cache));
		}

		/**
		* \brief Metoda pobierajaca zasób.
		*
		* Metoda pobiera lub tworzy zasób.
		* \param[in] identyfikator - Identyfikator zasobu.
		* \param[in] parametr - Adres pliku na bazie którgo ma zostaæ zainicjalizowany zasób.
		* \param[in] cache - Informacja czy zasób ma byæ lokalnie przechowywany.
		* \return WskaŸnik na zasób lub nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		Zasob::SharedPtr pobierzZasob(const Identyfikator& identyfikator, const Parametr& parametr, bool cache = false);

		/**
		* \brief Metoda pobierajaca zasób.
		*
		* Metoda pobiera lub tworzy zasób.
		* \param[in] identyfikator - Identyfikator zasobu.
		* \param[in] parametr - Adres pliku na bazie którgo ma zostaæ zainicjalizowany zasób.
		* \param[in] cache - Informacja czy zasób ma byæ lokalnie przechowywany.
		* \return WskaŸnik na zasób lub nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		template <class T_>
		inline std::shared_ptr<T_> pobierzZasob(const Identyfikator& identyfikator, const Parametr& parametr, bool cache = false){
			return std::dynamic_pointer_cast<T_>(pobierzZasob(identyfikator, parametr, cache));
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
		Zasob::SharedPtr pobierzUnikalnyZasob(const Parametr& parametr);

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
			return std::dynamic_pointer_cast<T_>(pobierzUnikalnyZasob(parametr));
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
		* \param[in] typ - Typ obiektu.
		* \param[in] funkcja - Funkcja tworz¹ca obiekt.
		* \return Zwracana jest wartoœc true, je¿eli uda siê zarejestrowaæ. Zwracana jest wartoœæ false, w przypadku b³êdu.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		bool rejestrujInicjalizator(const std::string& typ, Inicjalizator funkcja);

		/**
		* \brief Metoda sprawdzaj¹ca inicjalizator.
		*
		* Metoda sprawdza czy jest dostêpny inicjalizator dla danego typu.
		* \param[in] typ - Typ obiektu.
		* \return Zwracana jest wartoœc true, je¿eli jest dostêpny inicjalizator. Zwracana jest wartoœæ false, w przeciwnym przypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		bool dostepnyInicjalizator(const std::string& typ) const;

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
		* \brief Metoda usuwaj¹ca funkcjê inicjalizuj¹c¹.
		*
		* Metoda usuwa funkcjê inicjalizuj¹c¹ z zarz¹dcy zasobów.
		* \param[in] typ - Typ zasobu.
		* \return Zwracana jest funkcja inicjalizuj¹ca, je¿eli usuniêto. Zwracany jest nullptr, je¿eli funkcja nie istnieje.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		Inicjalizator wyrejestrujInicjalizator(const std::string& typ);

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
		
	private:
		GeneratorIdentyfikatorow generator_; /// Generator identyfikatorów.

		/**
		* \brief Metoda wczytuj¹ca zasób.
		*
		* Metoda wczytuje zasób do pamiêci.
		* \param[in] identyfikator - Identyfikator zasobu.
		* \param[in] parametr - Adres pliku na bazie którgo ma zostaæ zainicjalizowany zasób.
		* \param[in] cache - Informacja czy zasób ma byæ lokalnie przechowywany.
		* \return WskaŸnik na zasób lub nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		Zasob::SharedPtr wczytajZasob(const Identyfikator& identyfikator, const Parametr& parametr, bool cache = false);

		MapaZasobow zasobyPrzechowywane_; /// Obiekt przechowuj¹cy zasoby.
		MapaInicjalizatorow inicjalizatory_; /// Obiekt przechowuj¹cy inicjalizatory.

	};
};




