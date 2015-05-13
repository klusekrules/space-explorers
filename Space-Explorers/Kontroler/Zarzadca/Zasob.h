#pragma once
#include <memory>
#include "TypyProste\TypyProste.h"
#include "Utils\NonCopyable.h"

namespace SpEx{

	/**
	* \brief Klasa zawieraj¹ca interfejs zasobu.
	*
	* Klasa zawiera podstawowy interfejs dla zasobu.
	* \author Daniel Wojdak
	* \version 1
	* \date 06-08-2014
	*/
	class Zasob
		: se::NonCopyable
	{
		friend class ZarzadcaZasobow;
	public:
		typedef std::shared_ptr<Zasob> SharedPtr; /// Silny wskaŸnik na zasób.
		typedef std::weak_ptr<Zasob> WeakPtr; /// S³aby wskaŸnik na zasób.

		/**
		* \brief Domyœlny konstruktor.
		*
		* Domyœlny konstruktor.
		*/
		Zasob(const std::string& plik)
			: plik_(plik)
		{}

		/**
		* \brief Domyœlny destruktor.
		*
		* Domyœlny destruktor.
		*/
		virtual ~Zasob() = default;

		/**
		* \brief Metoda zwracaj¹ca identyfikator zasobu.
		*
		* Metoda Zwraca identyfikator zasobu.
		* \return Identyfikator zasobu.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		inline const STyp::Identyfikator& pobierzIdentyfikator() const{
			return identyfikator_;
		}

		inline const std::string& pobierzAdresPliku() const{
			return plik_;
		}

		/**
		* \brief Metoda inicjalizuj¹ca zasób.
		*
		* Metoda inicjalizuje zasób.
		* \return Zwracana jest wartoœæ true, je¿eli uda siê zainicjalizowaæ zasób poprawnie. Zwracana jest wartoœæ false, w przeciwnym wypadku.
		* \author Daniel Wojdak
		* \version 1
		* \date 06-08-2014
		*/
		virtual bool inicjalizuj() = 0; 

		virtual const std::string& nazwa() = 0;

	private:

		std::string plik_; /// Lokalizacja pliku.
		STyp::Identyfikator identyfikator_; /// Identyfikator zasobu.
	};
};
