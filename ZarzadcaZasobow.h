#pragma once
#include "GeneratorIdentyfikatorow.h"
#include "Zasob.h"
#include "NonCopyable.h"
#include <functional>

namespace SpEx {
	/**
	* \brief Klasa zarz�dzaj�ca zasobami.
	*
	* Klasa zarz�dzaj�ca zasobami, przechowuje wska�niki na zasoby.
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
		typedef std::pair< std::pair< Zasob::WeakPtr, Zasob::SharedPtr >, bool > WpisZasobu; /// Wpis zasobu przechowanego w zarz�dcy.
		typedef std::function< Zasob::SharedPtr(const Parametr&, bool) > Inicjalizator; /// Typ metody tworz�cej zas�b.
		typedef std::unordered_map < Identyfikator, WpisZasobu, STyp::IdTypeHash> MapaZasobow; /// Typ kontenera przechowuj�cego zasoby.
		typedef std::unordered_map < std::string, Inicjalizator> MapaInicjalizatorow; /// Typ kontenera przechowuj�cego inicjalizatory.

		/**
		* \brief Domy�lny konstruktor.
		*
		* Domy�lny konstruktor.
		*/
		ZarzadcaZasobow() = default;
		
		/**
		* \brief Domy�lny destruktor.
		*
		* Domy�lny destruktor.
		*/
		virtual ~ZarzadcaZasobow() = default;

		/**
		* \brief Metoda pobierajaca zas�b.
		*
		* Metoda pobiera lub tworzy zas�b.
		* \param[in] parametr - Adres pliku na bazie kt�rgo ma zosta� zainicjalizowany zas�b.
		* \param[in] cache - Informacja czy zas�b ma by� lokalnie przechowywany.
		* \return Wska�nik na zas�b lub nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		Zasob::SharedPtr pobierzZasob(const Parametr& parametr, bool cache = false);
		
		/**
		* \brief Metoda pobierajaca zas�b.
		*
		* Metoda pobiera lub tworzy zas�b.
		* \param[in] parametr - Adres pliku na bazie kt�rgo ma zosta� zainicjalizowany zas�b.
		* \param[in] cache - Informacja czy zas�b ma by� lokalnie przechowywany.
		* \return Wska�nik na zas�b lub nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		template <class T_>
		inline std::shared_ptr<T_> pobierzZasob(const Parametr& parametr, bool cache = false){
			return std::dynamic_pointer_cast<T_>(pobierzZasob(parametr, cache));
		}

		/**
		* \brief Metoda pobierajaca zas�b.
		*
		* Metoda pobiera lub tworzy zas�b.
		* \param[in] identyfikator - Identyfikator zasobu.
		* \param[in] parametr - Adres pliku na bazie kt�rgo ma zosta� zainicjalizowany zas�b.
		* \param[in] cache - Informacja czy zas�b ma by� lokalnie przechowywany.
		* \return Wska�nik na zas�b lub nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		Zasob::SharedPtr pobierzZasob(const Identyfikator& identyfikator, const Parametr& parametr, bool cache = false);

		/**
		* \brief Metoda pobierajaca zas�b.
		*
		* Metoda pobiera lub tworzy zas�b.
		* \param[in] identyfikator - Identyfikator zasobu.
		* \param[in] parametr - Adres pliku na bazie kt�rgo ma zosta� zainicjalizowany zas�b.
		* \param[in] cache - Informacja czy zas�b ma by� lokalnie przechowywany.
		* \return Wska�nik na zas�b lub nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		template <class T_>
		inline std::shared_ptr<T_> pobierzZasob(const Identyfikator& identyfikator, const Parametr& parametr, bool cache = false){
			return std::dynamic_pointer_cast<T_>(pobierzZasob(identyfikator, parametr, cache));
		}

		/**
		* \brief Metoda pobierajaca zas�b.
		*
		* Metoda pobiera lub tworzy zas�b.
		* \param[in] parametr - Adres pliku na bazie kt�rgo ma zosta� zainicjalizowany zas�b.
		* \return Wska�nik na zas�b lub nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		Zasob::SharedPtr pobierzUnikalnyZasob(const Parametr& parametr);

		/**
		* \brief Metoda pobierajaca zas�b.
		*
		* Metoda pobiera lub tworzy zas�b.
		* \param[in] parametr - Adres pliku na bazie kt�rgo ma zosta� zainicjalizowany zas�b.
		* \return Wska�nik na zas�b lub nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		template <class T_>
		inline std::shared_ptr<T_> pobierzUnikalnyZasob(const Parametr& parametr){
			return std::dynamic_pointer_cast<T_>(pobierzUnikalnyZasob(parametr));
		}

		/**
		* \brief Metoda pobiera informacje czy zas�b jest przechowywany przez zarz�dc�.
		*
		* Metoda pobiera informacje czy zas�b jest przechowywany lokalnie przez zarz�dc� zasob�w.
		* \param[in] identyfikator - Identyfikator zasobu.
		* \return Zwracana jest warto�c true, je�eli zas�b jest przechowywany. Zwracana jest warto�� false, w przeciwnym przypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		bool przechowywanyZasob(const Identyfikator& identyfikator) const;

		/**
		* \brief Metoda rejestruj�ca inicjalizator.
		*
		* Metoda rejestruje inicjalizator w zarz�dcy zasob�w.
		* \param[in] typ - Typ obiektu.
		* \param[in] funkcja - Funkcja tworz�ca obiekt.
		* \return Zwracana jest warto�c true, je�eli uda si� zarejestrowa�. Zwracana jest warto�� false, w przypadku b��du.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		bool rejestrujInicjalizator(const std::string& typ, Inicjalizator funkcja);

		/**
		* \brief Metoda sprawdzaj�ca inicjalizator.
		*
		* Metoda sprawdza czy jest dost�pny inicjalizator dla danego typu.
		* \param[in] typ - Typ obiektu.
		* \return Zwracana jest warto�c true, je�eli jest dost�pny inicjalizator. Zwracana jest warto�� false, w przeciwnym przypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		bool dostepnyInicjalizator(const std::string& typ) const;

		/**
		* \brief Metoda zwalaniaj�ca przechowywany zas�b.
		*
		* Metoda zwalnia zas�b przechowywany lokalnie w zarz�dcy.
		* \param[in] identyfikator - Identyfikator zasobu.
		* \return Zwracana jest warto�c true, je�eli jest uda�o si� zwolni� zas�b. Zwracana jest warto�� false, w przeciwnym przypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		bool zwolnijZasobPrzechowywany(const Identyfikator& identyfikator);

		/**
		* \brief Metoda usuwaj�ca funkcj� inicjalizuj�c�.
		*
		* Metoda usuwa funkcj� inicjalizuj�c� z zarz�dcy zasob�w.
		* \param[in] typ - Typ zasobu.
		* \return Zwracana jest funkcja inicjalizuj�ca, je�eli usuni�to. Zwracany jest nullptr, je�eli funkcja nie istnieje.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		Inicjalizator wyrejestrujInicjalizator(const std::string& typ);

		/**
		* \brief Metoda mapuje parametr na identyfikator.
		*
		* Metoda mapuje parametr tekstowy na identyfikator liczbowy.
		* \param[in] parametr - Adres pliku na bazie kt�rgo ma zosta� zainicjalizowany zas�b.
		* \param[out] identyfikator - Identyfikator zasobu.
		* \return Zwracana jest warto�c true, je�eli pierwszy raz odwo�ano si� do tego identyfikatora. Zwracana jest warto�� false, w przeciwnym przypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		bool mapujIdentyfikator(const Parametr& parametr, Identyfikator& identyfikator);
		
	private:
		GeneratorIdentyfikatorow generator_; /// Generator identyfikator�w.

		/**
		* \brief Metoda wczytuj�ca zas�b.
		*
		* Metoda wczytuje zas�b do pami�ci.
		* \param[in] identyfikator - Identyfikator zasobu.
		* \param[in] parametr - Adres pliku na bazie kt�rgo ma zosta� zainicjalizowany zas�b.
		* \param[in] cache - Informacja czy zas�b ma by� lokalnie przechowywany.
		* \return Wska�nik na zas�b lub nullptr.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		Zasob::SharedPtr wczytajZasob(const Identyfikator& identyfikator, const Parametr& parametr, bool cache = false);

		MapaZasobow zasobyPrzechowywane_; /// Obiekt przechowuj�cy zasoby.
		MapaInicjalizatorow inicjalizatory_; /// Obiekt przechowuj�cy inicjalizatory.

	};
};




